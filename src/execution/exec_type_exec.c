#include "minishell.h"

static void	use_execve(t_main_data *data, t_node_exec *exec_node,
				t_pipefd *pipe_struct);
static void	use_buildin(t_main_data *data, t_node_exec *exec_node,
				t_pipefd *pipe_struct);

void	type_exec(t_main_data *data, t_node *node, t_pipefd *pipe_struct)
{
	t_node_exec	*exec_node;

	if (node != NULL)
	{
		exec_node = (t_node_exec *)node;
		if (exec_node->file_path != NULL)
		{
			print_debugging_info_executer(INT_DEBUG, 4, NULL);
			print_debugging_info_executer(INT_DEBUG, 10, node);
			use_execve(data, exec_node, pipe_struct);
		}
		else
			printf(": command not found\n");
	}
	else
		printf("💀 Given node to EXEC is NULL! 💀\n");
}

static void	use_execve(t_main_data *data, t_node_exec *exec_node,
		t_pipefd *pipe_struct)
{
	if (false == exec_node->is_inbuilt)
	{
		print_debugging_info_executer(INT_DEBUG, 7, NULL);
		execve_handler(exec_node->file_path, exec_node->argv, exec_node->env);
	}
	else
	{
		print_debugging_info_executer(INT_DEBUG, 8, NULL);
		use_buildin(data, exec_node, pipe_struct);
	}
}

static void	use_buildin(t_main_data *data, t_node_exec *exec_node,
		t_pipefd *pipe_struct)
{
	char	**temp_str;
	int		i_count;

	temp_str = chose_buildin(data, exec_node, pipe_struct);
	if (is_last_node_exec(data->ast, exec_node->file_path)
		&& (temp_str != NULL))
	{
		i_count = 0;
		while (temp_str[i_count] != NULL)
		{
			printf("%s", temp_str[i_count++]);
		}
	}
	free_str_arr_null(temp_str);
}
