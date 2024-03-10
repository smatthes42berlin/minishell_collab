#include "minishell.h"

static bool	check_is_inbuilt(t_node *node)
{
	t_node_exec	*exec_node;

	if (node->type != EXEC)
		return (false);
	exec_node = (t_node_exec *)node;
	if (exec_node->is_inbuilt == false)
		return (false);
	return (true);
}

int	left_pipe_node(int *pipefd, t_main_data *data,
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
		ret = use_close(pipefd[0], err_msg);
		ret = write_str_arr_pipe(pipefd, str_arr, err_msg, true);
		ret = use_close(pipefd[1], err_msg);
		free_str_arr_null(str_arr);
	}
	return (ret);
}

int	right_pipe_node(int *pipefd, t_main_data *data,
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
