#include "minishell.h"

static	int	left_side(t_main_data *data, t_node_pipe *pipe_node,
				t_pipefd *pipe_struct, int *pipefd);
static int	nested_fork_right_pipe(int *pipefd, t_main_data *data,
				t_node_pipe *pipe_node, t_pipefd *pipe_struct);

int	type_pipe(t_main_data *data, t_node *node, t_pipefd *pipe_struct)
{
	int			pipefd[2];
	pid_t		cpid;
	t_node_pipe	*pipe_node;
	int			ret;
	int			status;

	ret = 0;
	pipe_node = (t_node_pipe *)node;
	pipe_handler(pipefd, "function \"type_pipe\"");
	cpid = fork_handler("function \"type_pipe\"");
	if (cpid == 0)
	{
		left_side(data, pipe_node, pipe_struct, pipefd);
		if (ret == -1)
			exit(ret);
		exit (0);
	}
	else
	{
		ret = nested_fork_right_pipe(pipefd, data, pipe_node, pipe_struct);
		waitpid(cpid, &status, 0);
		if (status == 65280)
			ret = -1;
	}
	return (ret);
}

static int	nested_fork_right_pipe(int *pipefd, t_main_data *data,
		t_node_pipe *pipe_node, t_pipefd *pipe_struct)
{
	pid_t	pid2;
	char	*err_msg;
	int		ret;
	int		status;

	ret = 0;
	err_msg = "function \"type_pipe\" nested pipe";
	pid2 = fork_handler(err_msg);
	if (pid2 == 0)
	{
		ret = right_pipe_node(pipefd, data, pipe_node, pipe_struct);
		free_main_exit(data, 0);
		free(pipe_struct);
		exit(ret);
	}
	else
	{
		use_close(pipefd[0], err_msg);
		use_close(pipefd[1], err_msg);
		waitpid(pid2, &status, 0);
		ret = get_process_exit_code(status);
	}
	return (ret);
}

static	int	left_side(t_main_data *data, t_node_pipe *pipe_node,
		t_pipefd *pipe_struct, int *pipefd)
{
	int	ret;

	ret = left_pipe_node(pipefd, data, pipe_node, pipe_struct);
	free_main_exit(data, 0);
	free(pipe_struct);
	return (ret);
}
