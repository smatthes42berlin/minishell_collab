#include "minishell.h"

void	type_exec(t_main_data *data, t_node *node, t_pipefd *pipe_struct)
{
	t_node_exec	*exec_node;
	char		**temp_str;
	int			i_count;

	if (node == NULL)
	{
		printf("the point is null!");
		return ;
	}
	exec_node = (t_node_exec *)node;
	print_debugging_info_executer(INT_DEBUG, 4, NULL);
	//print_exec_node(exec_node, 1);
	if (exec_node->file_path == NULL)
		printf("%s :  command not found\n", exec_node->argv[0]);
	print_debugging_info_executer(INT_DEBUG, 10, node);
	if (false == exec_node->is_inbuilt)
	{
		print_debugging_info_executer(INT_DEBUG, 7, NULL);
		execve_handler(exec_node->file_path, exec_node->argv, exec_node->env);
	}
	else
	{
		print_debugging_info_executer(INT_DEBUG, 8, NULL);
		//temp_str = NULL;
		temp_str = chose_buildin(data, exec_node, pipe_struct);
		if (is_last_node(data->ast, exec_node->file_path) && (temp_str != NULL))
		{
			i_count = 0;
			while (temp_str[i_count] != NULL)
			{
				printf("%s", temp_str[i_count++]);
			}
		}
		// printf ("printing in exec \n");
		// print_str_arr_null(temp_str);
		free_str_arr_null(temp_str);
	}
}