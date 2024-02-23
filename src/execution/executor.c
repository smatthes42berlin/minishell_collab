#include "minishell.h"

static void	read_pipe(t_main_data *data, t_pipefd *pipe_struct);
static void	env_add_clr(t_main_data *data, char *env_var);
// static void	free_main(t_main_data *data);

// void manuel_test_mode(t_main_data *data)
// {
// 	//free_ast(data->ast);
// 	data->ast = NULL;
// 	data->ast = malloc_handler(sizeof(t_node));

// 		// t_node_exec *test = set_cmd_1();
// 		// data->ast->type = EXEC;

// 		t_node_pipe *test = set_cmd_2();
// 		data->ast->type = PIPE;

// 	data->ast =(void *)test;
// }

int	executor(t_main_data *data)
{
	pid_t		pid;
	int			pipefd[2];
	int			exit_code_pipe[2];
	int			exit_code;
	int			status;
	t_pipefd	*pipe_struct;

	if (PRINT_DEBUG_1)
		printf("##########################################################\n");
	print_debugging_info_executer(INT_DEBUG, 1, NULL);
	pipe_handler(pipefd, "function \"executor\" main pipe");
	pipe_handler(exit_code_pipe, "function \"executor\" exit_code_pipe");
	pipe_struct = malloc(sizeof(t_pipefd));
	if (!pipe_struct)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
			"function \"executor\""});
	pipe_struct->pipefd = pipefd;
	pid = fork_handler("function executor");
	if (pid == 0)
	{
		// manuel_test_mode(data);
		navigate_tree_forward(data, data->ast, pipe_struct);
		// free(pipe_struct);
		free_ast(data->ast);
		free_main_exit(data, 0);
		free_main_exit(data, 0);
		free_main_exit(data, 0); // genauers Prüfen im Valgrind
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (data->ast->type != PIPE)
			exit_code = get_process_exit_code(status);
		else
			pipe_setting_exit_code(exit_code_pipe, false, &exit_code,
				"function \"executor\" pipe");
		//data->exit_code = exit_code;
		//printf("Iam in child an the error_pipecode are |%d|\n", exit_code);
		//printf("exitcode ist executer |%i|\n", data->exit_code);
	}
	read_pipe(data, pipe_struct);
	free(pipe_struct);
	print_debugging_info_executer(INT_DEBUG, 2, NULL);
	if (PRINT_DEBUG_1)
		printf("##########################################################\n");
	// printf("env_HOME |%s|\n", env_get_var(data, "HOME"));
	// printf("env_PWD |%s|\n", env_get_var(data, "PWD"));
	return (0);
}

static void	read_pipe(t_main_data *data, t_pipefd *pipe_struct)
{
	ssize_t	bytes_read;
	int		start;
	int		i_count;
	char	buffer[BUFFER_SIZE + 1];

	start = 0;
	i_count = 0;
	use_close(pipe_struct->pipefd[1], "fuction \"read pipe\" for executor");
	while ((bytes_read = read(pipe_struct->pipefd[0], buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		i_count = 0;
		while (i_count < bytes_read)
		{
			if (buffer[i_count] == '\n' || buffer[i_count] == '\0')
			{
				buffer[i_count] = '\0';
				env_add_clr(data, &buffer[start]);
				start = i_count + 1;
			}
			i_count++;
		}
		if (start < bytes_read)
		{
			ft_memmove(buffer, &buffer[start], bytes_read - start);
			bytes_read = bytes_read - start;
			start = 0;
		}
		else
		{
			start = 0;
		}
	}
	close(pipe_struct->pipefd[0]);
}

static void	env_add_clr(t_main_data *data, char *env_var)
{
	if (data->ast->type == PIPE)
	{
		if (ft_strncmp(env_var, ADD_ENV, ft_strlen(ADD_ENV)) == 0)
		{
			print_debugging_info_executer(INT_DEBUG, 20, env_var);
			env_set_var(data, env_var + ft_strlen(ADD_ENV));
		}
		else if (ft_strncmp(env_var, CLR_ENV, ft_strlen(CLR_ENV)) == 0)
		{
			print_debugging_info_executer(INT_DEBUG, 21, env_var);
			env_del_var(data, env_var + ft_strlen(CLR_ENV));
		}
		else if (ft_strncmp(env_var, ADD_CD, ft_strlen(ADD_CD)) == 0)
		{
			print_debugging_info_executer(INT_DEBUG, 22, env_var);
			if (chdir(env_var + ft_strlen(ADD_CD) + 4) < 0)
				throw_error_custom((t_error_ms){errno, EPART_EXECUTOR,
					EFUNC_CHDIR, "function \"env_add_clr\""});
		}
	}
	if (ft_strncmp(env_var, EXIT_CODE, ft_strlen(EXIT_CODE)) == 0)
	{
		print_debugging_info_executer(INT_DEBUG, 22, env_var);
		// if (chdir(env_var + ft_strlen(ADD_CD) + 4) == -1)
		// 	error_code_handler(errno, "ERR-chdir", "CD -Command --> ", env_var
		// 		+ ft_strlen(ADD_CD) + 4);	
	}
}
