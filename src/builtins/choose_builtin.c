#include "minishell.h"

t_node_exec	*check_buildin(t_node *node)
{
	t_node_exec	*exec_node;

	if (node->type != EXEC)
		return (NULL);
	exec_node = (t_node_exec *)node->node_type;
	if (exec_node->inbuilt == false)
		return (NULL);
	return (exec_node);
}

char	*chose_buildin(t_main_data *data, t_node_exec *node, t_pipefd *pipe_struct)
{

	//!!!!!unused data for debugger (data) ---> delet later 
	if (data->ast == NULL)
		printf("AST == NULL!\n");

	//!!!!!
	if (str_are_equal(node->file_path, "pwd"))
	{
		return (build_pwd());
	}
	if (str_are_equal(node->file_path, "cd"))
	{
		return (build_cd(node, pipe_struct));
	}
	return (NULL);
}

bool	check_and_choose_buildin(t_main_data *data, t_node *node, t_pipefd *pipe_struct_pipe, t_pipefd *pipe_struct_main)
{
	t_node_exec *exec_node;
	char *temp_str;

	exec_node = check_buildin(node);
	if (NULL == exec_node)
	{
		return (false);
	}
	temp_str = chose_buildin(data ,exec_node, pipe_struct_main);
	pipe_setting(pipe_struct_pipe->pipefd, pipe_struct_pipe->direction, temp_str);
	free(temp_str);
	return (true);
}