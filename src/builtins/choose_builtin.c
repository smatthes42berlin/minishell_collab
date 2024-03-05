#include "minishell.h"

char	**chose_buildin(t_main_data *data, t_node_exec *node,
		t_pipefd *pipe_struct, bool from_redir)
{
	printf(" IN chosen \n");
	print_debugging_info_executer(INT_DEBUG, 9, NULL);
	if (str_are_equal(node->file_path, "pwd"))
		return (build_pwd(data, node, pipe_struct, from_redir));
	if (str_are_equal(node->file_path, "cd"))
		return (build_cd(data, node, pipe_struct));
	if (str_are_equal(node->file_path, "echo"))
		return (build_echo(data, node, pipe_struct, from_redir));
	if (str_are_equal(node->file_path, "export"))
		return (build_export(data, node, pipe_struct));
	if (str_are_equal(node->file_path, "unset"))
		return (build_unset(data, node, pipe_struct));
	if (str_are_equal(node->file_path, "env"))
		return (build_env(data, node, pipe_struct, from_redir));
	if (str_are_equal(node->file_path, "exit"))
		return (build_exit(data, node, pipe_struct));
	
	return (NULL);
}
