#include "minishell.h"

// make pipe
// fork
// read all lines in child
// write string to pipe
// write first value as stringlength
// free in child
// exit child
// read string in parent

int	read_heredoc(t_here_doc_info *hdoc_info, t_token **hdoc_operator_token)
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
		if (close(fd[0] == -1))
			return (printf("Error: closing pipe"));
		return (child_read_hdoc(hdoc_info));
	}
	else
	{
		if (close(fd[1] == -1))
			return (printf("Error: closing pipe"));
		return (parent_get_str_child(hdoc_operator_token, fd, pid));
	}
	printf("1: $%s$\n", hdoc_info->delim_raw);
	printf("2: $%s$\n", (*hdoc_operator_token)->value);
}

int	parent_get_str_child(t_token **hdoc_operator_token, int fd[2], int pid)
{
	int	res_wait;
	int	status;
	int	str_len;

	res_wait = waitpid(pid, &status, 0);
	if (res_wait == -1)
		printf("Error: problem waiting for child process");
	if (WIFEXITED(status))
		res_wait = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		res_wait = WTERMSIG(status);
	
	return (0);
}

int	child_read_hdoc(t_here_doc_info *hdoc_info)
{
}

// if (close(data->fd_pipe[0]) == -1 || close(data->fd_pipe[1]) == -1)
// 		clean_exit_error(data, 1, "");
// 	res_wait_1 = waitpid(data->child_1_pid, &status_1, 0);
// 	res_wait_2 = waitpid(data->child_2_pid, &status_2, 0);
// 	if (res_wait_1 == -1 || res_wait_2 == -1)
// 		clean_exit_error(data, 1, "");
// 	if (WIFEXITED(status_2))
// 		res_wait_2 = WEXITSTATUS(status_2);
// 	if (WIFSIGNALED(status_2))
// 		res_wait_2 = WTERMSIG(status_2);
// 	clean_exit_main(data, res_wait_2);