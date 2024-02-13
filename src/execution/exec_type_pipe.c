#include "minishell.h"

static void	type_pipe_nested_pid(t_main_data *data, t_node_pipe *pipe_node,
				pid_t main_pid, int *pipefd, bool direction,
				t_pipefd *pipe_struct_main);


void	type_pipe(t_main_data *data, t_node *node, t_pipefd *pipe_struct)
{
	t_node_pipe	*pipe_node;
	int			pipefd[2];
	pid_t		main_pid;

	pipe_node = (t_node_pipe *)node;
	print_debugging_info_executer(INT_DEBUG, 6, NULL);;
	pipe_handler(pipefd);
	main_pid = fork_handler();
	if (main_pid == 0)
	{
		// if (false == check_and_choose_buildin(data, pipe_node->left_node,
		// 		pipefd, true, pipe_struct))
		// {
			pipe_setting(pipefd, true, NULL);
			navigate_tree_forward(data, pipe_node->left_node, pipe_struct);
		// }
	}
	else
	{
		type_pipe_nested_pid(data, pipe_node, main_pid, pipefd, false,
			pipe_struct);
	}
}

static void	type_pipe_nested_pid(t_main_data *data, t_node_pipe *pipe_node,
		pid_t main_pid, int *pipefd, bool direction, t_pipefd *pipe_struct_main)
{
	pid_t	nested_pid;

	pipe_setting(pipefd, direction, NULL);
	nested_pid = fork_handler();
	if (nested_pid == 0)
	{
		// if (false == check_and_choose_buildin(data, pipe_node->right_node,
		// 		pipefd, direction, pipe_struct_main))
		// {
			navigate_tree_forward(data, pipe_node->right_node,
				pipe_struct_main);
	//	}
	}
	else
	{
		waitpid(main_pid, NULL, 0);
		waitpid(nested_pid, NULL, 0);
	}
}