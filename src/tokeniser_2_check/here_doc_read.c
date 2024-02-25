#include "minishell.h"

static int	init_pipe_fork(t_here_doc_info *hdoc_info);

int	read_heredoc(t_here_doc_info *hdoc_info, t_list_d **hdoc_op_token)
{
	if (init_pipe_fork(hdoc_info))
		return (1);
	if (hdoc_info->pid == 0)
	{
		if (close(hdoc_info->fd[0]) == -1)
			return (throw_error_custom((t_error_ms){errno, EPART_TOKENISER,
					EFUNC_CLOSE, "hdoc closing pipe"}));
		if (restore_default_signals(SIGINT))
			return (1);
		return (child_read_hdoc(hdoc_info, hdoc_info->fd));
	}
	else
	{
		if (close(hdoc_info->fd[1]) == -1)
			return (throw_error_custom((t_error_ms){errno, EPART_TOKENISER,
					EFUNC_CLOSE, "hdoc closing pipe"}));
		return (parent_get_str_child(hdoc_op_token, hdoc_info->fd,
				hdoc_info->pid, hdoc_info));
	}
}

static int	init_pipe_fork(t_here_doc_info *hdoc_info)
{
	if (pipe(hdoc_info->fd) == -1)
		return (throw_error_custom((t_error_ms){errno, EPART_TOKENISER,
				EFUNC_PIPE, "hdoc creating pipe"}));
	hdoc_info->pid = fork();
	if (hdoc_info->pid == -1)
		return (throw_error_custom((t_error_ms){errno, EPART_TOKENISER,
				EFUNC_FORK, "hdoc forking"}));
	return (0);
}
