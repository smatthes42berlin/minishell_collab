#include "minishell.h"

static bool	was_signaled(int status, t_here_doc_info *hdoc_info);

int	parent_get_str_child(t_list_d **hdoc_op_token, int fd[2], int pid,
		t_here_doc_info *hdoc_info)
{
	int		res_wait;
	int		status;
	char	*res;

	res_wait = waitpid(pid, &status, 0);
	if (res_wait == -1)
		return (throw_error_custom((t_error_ms){errno, EPART_TOKENISER,
				EFUNC_WAIT, "hdoc waiting for child process"}));
	if (WIFEXITED(status))
		res_wait = WEXITSTATUS(status);
	if (was_signaled(status, hdoc_info))
		return (1);
	if (res_wait)
		return (1);
	if (read_whole_file(fd[0], &res))
		return (throw_error_custom((t_error_ms){errno, EPART_TOKENISER,
				EFUNC_READ, "hdoc reading from pipe"}));
	if (close(fd[0]) == -1)
		return (throw_error_custom((t_error_ms){errno, EPART_TOKENISER,
				EFUNC_PIPE, "hdoc closing pipe"}));
	if (add_heredoc_str_token(hdoc_op_token, res, hdoc_info))
		return (1);
	return (0);
}

static bool	was_signaled(int status, t_here_doc_info *hdoc_info)
{
	if (WIFSIGNALED(status))
	{
		hdoc_info->signal_exit = WTERMSIG(status) + 128;
		return (true);
	}
	return (false);
}

int	add_heredoc_str_token(t_list_d **hdoc_op_token, char *res,
		t_here_doc_info *hdoc_info)
{
	t_list_d	*next_token;
	t_token		*next_token_val;
	char		*tmp;

	next_token = (*hdoc_op_token)->next;
	next_token_val = next_token->content;
	if (hdoc_info->quoted)
	{
		if (ft_join_n_str(&tmp, 3, "'", res, "'") == -1)
		{
			free(res);
			return (throw_error_custom((t_error_ms){errno, EPART_TOKENISER,
					EFUNC_MALLOC, "hdoc adding single quotes"}));
		}
		free(res);
		res = tmp;
	}
	free(next_token_val->value);
	next_token_val->value = res;
	next_token_val->type = T_HEREDOC;
	return (0);
}
