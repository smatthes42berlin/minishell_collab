#include "minishell.h"

char	**chose_buildin(t_main_data *data, t_node_exec *node,
		t_pipefd *pipe_struct)
{
	print_debugging_info_executer(INT_DEBUG, 9, NULL);
	if (str_are_equal(node->file_path, "pwd"))
		return (build_pwd(true));
	if (str_are_equal(node->file_path, "cd"))
		return (build_cd(data, node, pipe_struct));
	if (str_are_equal(node->file_path, "echo"))
		return (build_echo(data, node));
	if (str_are_equal(node->file_path, "export"))
		return (build_export(data, node, pipe_struct));
	if (str_are_equal(node->file_path, "unset"))
		return (build_unset(data, node, pipe_struct));
	if (str_are_equal(node->file_path, "env"))
		return (build_env(data));
	return (NULL);
}

bool	check_is_inbuilt(t_main_data *data, t_node *node,
		t_pipefd *pipe_struct, int *pipefd)
{
	t_node_exec *exec_node;

	if (!pipefd[1] && pipe_struct->direction && data->ast->type == EXEC)
		printf("NOtingChekcisbuildtn");

	if (node->type != EXEC)
		return (false);
	exec_node = (t_node_exec *)node;
	if (exec_node->is_inbuilt == false)
		return (false);
	else 
		pipe_setting(pipefd, true, chose_buildin(data, exec_node, pipe_struct),
			"function \"type pipe\" child");
	return (true);
}