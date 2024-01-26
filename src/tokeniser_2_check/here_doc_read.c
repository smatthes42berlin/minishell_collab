#include "minishell.h"

int	read_heredoc(t_here_doc_info *hdoc_info, t_list_d **hdoc_op_token)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return (printf("Error: creating pipe"));
	pid = fork();
	if (pid == -1)
		return (printf("Error: forking"));
	if (pid == 0)
	{
		if (close(fd[0]) == -1)
			return (printf("Error: closing pipe"));
		return (child_read_hdoc(hdoc_info, fd));
	}
	else
	{
		if (close(fd[1]) == -1)
			return (printf("Error: closing pipe"));
		return (parent_get_str_child(hdoc_op_token, fd, pid, hdoc_info));
	}
}
