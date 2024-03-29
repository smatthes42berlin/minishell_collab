#include "minishell.h"

char	**chose_buildin(t_main_data *data, t_node_exec *node,
		t_pipefd *pipe_struct)
{
	if (str_are_equal(node->file_path, "echo"))
		return (build_echo(data, node, pipe_struct));
	if (str_are_equal(node->file_path, "exit"))
		return (build_exit(data, node, pipe_struct));
	if (check_flag_err_buildin(pipe_struct, node->argv,
			"flage error inbuild"))
		return (NULL);
	else
	{
		if (str_are_equal(node->file_path, "pwd"))
			return (build_pwd(pipe_struct));
		if (str_are_equal(node->file_path, "cd"))
			return (build_cd(data, node, pipe_struct));
		if (str_are_equal(node->file_path, "export"))
			return (build_export(data, node, pipe_struct));
		if (str_are_equal(node->file_path, "unset"))
			return (build_unset(data, node, pipe_struct));
		if (str_are_equal(node->file_path, "env"))
			return (build_env(data, node, pipe_struct));
	}
	return (NULL);
}
