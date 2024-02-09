#include "minishell.h"

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
		return (build_cd(data, node, pipe_struct));
	}
	if (str_are_equal(node->file_path, "echo"))
	{
		return (build_echo(node));
	}
	return (NULL);
}