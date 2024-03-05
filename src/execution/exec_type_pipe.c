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
	char		*err_msg;
	int			ret;

	ret = 0;
	err_msg = "function \"type_pipe\"";
	pipe_node = (t_node_pipe *)node;
	pipe_handler(pipefd, err_msg);
	cpid = fork_handler(err_msg);
	if (cpid == 0)
		left_pipe_node(pipefd, data, pipe_node, pipe_struct);
	else
	{
		ret = nested_fork_right_pipe(pipefd, data, pipe_node, pipe_struct);
		waitpid(cpid, NULL, 0);
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
		ret = right_pipe_node(pipefd, data, pipe_node, pipe_struct);
	else
	{
		use_close(pipefd[0], err_msg);
		use_close(pipefd[1], err_msg);
		if (pipe_node->right_node->type == PIPE)
			waitpid(pid2, NULL, 0);
		else
		{
			waitpid(pid2, &status, 0);
			write_exit_status_to_pipe(status, pipe_struct, err_msg);
		}
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
		ret = navigate_tree_forward(data, pipe_node->left_node, pipe_struct);
	}
	else
	{
		exec_node = (t_node_exec *)pipe_node->left_node;
		str_arr = chose_buildin(data, exec_node, pipe_struct, true);
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
	if (check_is_inbuilt(pipe_node->left_node) 
		&& check_is_inbuilt(pipe_node->right_node))
	{
		ret = use_close(pipefd[1], err_msg);
		ret = read_str_arr_pipe(pipefd);
		ret = use_close(pipefd[0], err_msg);
		ret = navigate_tree_forward(data, pipe_node->right_node, pipe_struct);
	}
	else
	{
		ret = use_close(pipefd[1], err_msg);
		ret = use_dup2(pipefd[0], STDIN_FILENO, err_msg);
		ret = use_close(pipefd[0], err_msg);
		ret = navigate_tree_forward(data, pipe_node->right_node, pipe_struct);
	}
	return (ret);
}
