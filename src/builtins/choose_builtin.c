#include "minishell.h"

char	**chose_buildin(t_main_data *data, t_node_exec *node, t_pipefd *pipe_struct)
{

	print_debugging_info_executer(INT_DEBUG, 9, NULL);
	if (str_are_equal(node->file_path, "pwd"))
	{
		return (build_pwd(true));
	}
	if (str_are_equal(node->file_path, "cd"))
	{
		return (build_cd(data, node, pipe_struct));
	}
	if (str_are_equal(node->file_path, "echo"))
	{
		return (build_echo(data, node));
	}
	return (NULL);
}