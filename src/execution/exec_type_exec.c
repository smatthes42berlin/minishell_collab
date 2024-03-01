#include "minishell.h"

static void	use_execve(t_main_data *data, t_node_exec *exec_node,
				t_pipefd *pipe_struct);
static void	use_buildin(t_main_data *data, t_node_exec *exec_node,
				t_pipefd *pipe_struct);

void	type_exec(t_main_data *data, t_node *node, t_pipefd *pipe_struct)
{
	t_node_exec	*exec_node;
	pid_t 	pid;
	int 	status;
	int 	ret;
	char	*tmp_str;


	if (node != NULL)
	{
		exec_node = (t_node_exec *)node;
		if (exec_node->file_path != NULL)
		{
			print_debugging_info_executer(INT_DEBUG, 4, NULL);
			print_debugging_info_executer(INT_DEBUG, 10, node);
			pid = fork_handler("functtion type_exec -> filepath NULL");
			if (pid == 0)
			{
				use_execve(data, exec_node, pipe_struct);
			}
			else
			{
				waitpid(pid, &status, 0);
				ret = get_process_exit_code(status);
				//printf("I found error %d %d\n", ret, status);
				pipe_setting_exit_code(pipe_struct->pipefd_exit_code, 
					true, &ret, "err");
			}
		}
		else
		{
			pid = fork_handler("functtion type_exec -> filepath NULL");
			if (pid == 0)
			{
				if (access_handler(exec_node->argv[0], FILE_EXISTS, 0) < 0)
				{
					tmp_str = use_strjoin(exec_node->argv[0], ": command not found", "use_strjoin");
					exit(throw_error_mimic_bash(tmp_str, 127));
				}
				else if (access_handler(exec_node->argv[0],
						FILE_EXECUTABLE, 0) < 0)
				{
					tmp_str = use_strjoin(exec_node->argv[0], ": Permission denied", "use_strjoin");
					exit(throw_error_mimic_bash(tmp_str, 126));
				}
			}
			else
			{
				waitpid(pid, &status, 0);
				ret = get_process_exit_code(status);
				//printf("I found error %d %d\n", ret, status);
				pipe_setting_exit_code(pipe_struct->pipefd_exit_code, 
					true, &ret, "err");
			}
		}
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
