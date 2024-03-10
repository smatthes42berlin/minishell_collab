#include "minishell.h"

static int	left_pipe_node(int *pipefd, t_main_data *data,
				t_node_pipe *pipe_node, t_pipefd *pipe_struct);
static int	right_pipe_node(int *pipefd, t_main_data *data,
				t_node_pipe *pipe_node, t_pipefd *pipe_struct);
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
		ret = left_pipe_node(pipefd, data, pipe_node, pipe_struct);
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

bool	check_is_inbuilt(t_node *node)
{
	t_node_exec	*exec_node;

	if (node->type != EXEC)
		return (false);
	exec_node = (t_node_exec *)node;
	if (exec_node->is_inbuilt == false)
		return (false);
	return (true);
}

static int	left_pipe_node(int *pipefd, t_main_data *data,
		t_node_pipe *pipe_node, t_pipefd *pipe_struct)
{
	char		*err_msg;
	int			ret;
	char		**str_arr;
	t_node_exec	*exec_node;

	err_msg = "function \"type_pipe\" --> left node";
	if (!check_is_inbuilt(pipe_node->left_node))
	{
		ret = use_close(pipefd[0], err_msg);
		ret = use_dup2(pipefd[1], STDOUT_FILENO, err_msg);
		ret = use_close(pipefd[1], err_msg);
		if (ret != -1)
			ret = navigate_tree_forward(data, pipe_node->left_node,
					pipe_struct);
	}
	else
	{
		exec_node = (t_node_exec *)pipe_node->left_node;
		str_arr = chose_buildin(data, exec_node, pipe_struct);
		print_str_arr_null(str_arr);
		ret = use_close(pipefd[0], err_msg);
		ret = write_str_arr_pipe(pipefd, str_arr, err_msg, true);
		ret = use_close(pipefd[1], err_msg);
		free_str_arr_null(str_arr);
	}
	return (ret);
}

static int	right_pipe_node(int *pipefd, t_main_data *data,
		t_node_pipe *pipe_node, t_pipefd *pipe_struct)
{
	char	*err_msg;
	int		ret;

	err_msg = "function \"type_pipe\" --> right node";
	ret = use_close(pipefd[1], err_msg);
	if (ret != -1)
	{
		if (check_is_inbuilt(pipe_node->left_node)
			&& check_is_inbuilt(pipe_node->right_node))
			ret = read_str_arr_pipe(pipefd);
		else
			ret = use_dup2(pipefd[0], STDIN_FILENO, err_msg);
		ret = use_close(pipefd[0], err_msg);
		if (ret != -1)
			ret = navigate_tree_forward(data, pipe_node->right_node,
					pipe_struct);

	}
	return (ret);
}
