#include "minishell.h"

static int	read_pipe(t_main_data *data, t_pipefd *pipe_struct);
static int	env_add_clr(t_main_data *data, char *env_var);
static void	free_main(t_main_data *data);

/**
// void manuel_test_mode(t_main_data *data)
// {
// 	//free_ast(data->ast);
// 	data->ast = NULL;
// 	data->ast = malloc(sizeof(t_node));

// 		// t_node_exec *test = set_cmd_1();
// 		// data->ast->type = EXEC;

// 		t_node_pipe *test = set_cmd_2();
// 		data->ast->type = PIPE;

// 	data->ast =(void *)test;
// }

// void check_systamstate(void)
// {
// 	if (systemstate == STATE_SIGINT)
// 		printf("checked Systemstate \n\n");

// }
*/

int	executor(t_main_data *data)
{
	pid_t		pid;
	int			pipefd[2];
	int			status;
	t_pipefd	*pipe_struct;
	int			res_wait_2;
	int			exit_code_pipe[2];
	int			get_exit_code;

	if (PRINT_DEBUG_1)
		printf("\n\n##########################################################\n");
	print_debugging_info_executer(INT_DEBUG, 1, NULL);
	pipe_handler(pipefd, "function \"executor\" main pipe");
	pipe_handler(exit_code_pipe, "function \"executor\" exit_code_pipe");
	pipe_struct = malloc(sizeof(t_pipefd));
	if (!pipe_struct)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
			"function \"executor\""});
	pipe_struct->pipefd = pipefd;
	pipe_struct->pipefd_exit_code = exit_code_pipe;
	pid = fork_handler("function \"executor\"");
	if (pid < 0)
	{
		free_main(data);
		return (-1);
	}
	if (pid == 0)
	{

		if (restore_default_signals(SIGQUIT + SIGINT))
			exit(errno);
		navigate_tree_forward(data, data->ast, pipe_struct);
		free_main(data);
	}
	else
	{
		waitpid(pid, &status, 0);
		
		if (WIFSIGNALED(status))
		{
			res_wait_2 = WTERMSIG(status);
			if (WIFSIGNALED(status))
			{
				res_wait_2 = WTERMSIG(status);
				if (res_wait_2 == SIGINT)
					printf("\n");
				if (res_wait_2 == SIGQUIT)
					printf("Quit (core dumped)\n");
			}
		}

		if (data->ast->type != PIPE && data->ast->type != REDIR)
		{
			get_exit_code = get_process_exit_code(status);
			//printf("EXITCODE %i staus %d\n", get_exit_code, status);
		}
		else
		{
			pipe_setting_exit_code(exit_code_pipe, false, &get_exit_code, "function \"executor\" pipe");
			//printf("EXITCODE PIPE  %i\n", get_exit_code);
		}
		set_exit_code(get_exit_code);
		
	}
	if (read_pipe(data, pipe_struct) == -1)
	{
		free(pipe_struct);
		return (-1);
	}
	free(pipe_struct);
	print_debugging_info_executer(INT_DEBUG, 2, NULL);
	if (PRINT_DEBUG_1)
		printf("##########################################################\n");
	return (0);
}

static int read_pipe(t_main_data *data, t_pipefd *pipe_struct) {
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE + 1];
    char *line_start = buffer;
    int line_length = 0;

    use_close(pipe_struct->pipefd[1], "function \"read pipe\" for executor");
    while ((bytes_read = read(pipe_struct->pipefd[0], buffer + line_length, BUFFER_SIZE - line_length)) > 0) {
        line_length += bytes_read;
        buffer[line_length] = '\0';

        char *newline;
        while ((newline = strchr(line_start, '\n')) != NULL)
		{
            *newline = '\0';
            if (env_add_clr(data, line_start) == -1)
                return -1;
         //   printf("READ BUFFER : %s\n", line_start);
            line_start = newline + 1;
        }
        int remaining_data = buffer + line_length - line_start;
        ft_memmove(buffer, line_start, remaining_data);
        line_length = remaining_data;
    }
    if (line_length > 0) {
        if (env_add_clr(data, line_start) == -1)
            return -1;
     //   printf("READ BUFFER : %s\n", line_start);
    }

    use_close(pipe_struct->pipefd[0], "function \"read pipe\" for executor");
    return 0;
}


/**
static int read_pipe(t_main_data *data, t_pipefd *pipe_struct) {
    ssize_t bytes_read;
    int i_count;
    char buffer[BUFFER_SIZE + 1];

    i_count = 0;
	use_close(pipe_struct->pipefd[1], "fuction \"read pipe\" for executor");
    while ((bytes_read = read(pipe_struct->pipefd[0], buffer, BUFFER_SIZE)) > 0) 
	{
        buffer[bytes_read] = '\0';
        i_count = 0;
        while (i_count < bytes_read) {
            if (buffer[i_count] == '\n' || buffer[i_count] == '\0') 
			{
                buffer[i_count] = '\0';
                if (env_add_clr(data, buffer) == -1)
                    return (-1);
				printf("READ BUFFER : %s\n", buffer);
                buffer[0] = '\0';
            }
            i_count++;
        }
    }
    if (i_count > 0) 
	{
        if (env_add_clr(data, buffer) == -1)
            return -1;
		printf("READ BUFFER : %s\n", buffer);
    }
	use_close(pipe_struct->pipefd[0], "fuction \"read pipe\" for executor");
    return 0;
}
*/


static int	env_add_clr(t_main_data *data, char *env_var)
{
//	printf("GIVENARG : %s\n", env_var );
	if (data->ast->type != PIPE)
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
		//printf ("Given for exit code %s\n", env_var);
		int exit_code;
		print_debugging_info_executer(INT_DEBUG, 30, env_var);
		if (ft_strncmp(env_var + ft_strlen(EXIT_CODE), "exit=",
				ft_strlen("exit=")) == 0)
		{
			exit_code = ft_atoi(env_var + ft_strlen(EXIT_CODE) + ft_strlen("exit="));
			if (exit_code != 0)
			{
				if (ft_strchr(env_var, '_') == NULL)
					set_exit_code(exit_code);
				else
				{
					char *str_err_msg = (ft_strchr(env_var, '_') + ft_strlen("_MSG="));
					throw_error_mimic_bash(str_err_msg, exit_code);
				}
			}
		}
		else
			set_exit_code(0);
	}
	if (ft_strncmp(env_var, EXIT, ft_strlen(EXIT)) == 0)
	{
		//free_main(data);
		return (-1);
	}
	return (0);
}


static void	free_main(t_main_data *data)
{
	free_ast(data->ast);
	free_main_exit(data, 0);
	free_main_exit(data, 0);
	free_main_exit(data, 0);
}