#include "minishell.h"

static void	read_pipe(t_main_data *data, t_pipefd *pipe_struct);
static void	env_add_clr(t_main_data *data, char *env_var);

void manuel_test_mode(t_main_data *data)
{
	//free_ast(data->ast);
	data->ast = NULL;
	data->ast = malloc_handler(sizeof(t_node));

		// t_node_exec *test = set_cmd_1();
		// data->ast->type = EXEC;

		t_node_pipe *test = set_cmd_2();
		data->ast->type = PIPE;

	data->ast =(void *)test;
}


int	executor(t_main_data *data)
{
	pid_t		pid;
	int			pipefd[2];
	t_pipefd	*pipe_struct;

	printf("##########################################################\n");
	print_debugging_info_executer(INT_DEBUG, 1, NULL);
	pipe_handler(pipefd);
	pipe_struct = malloc_handler(sizeof(t_pipefd));
	pipe_struct->pipefd = pipefd;
	pid = fork_handler();
	
	if (pid == 0)
	{
		navigate_tree_forward(data, data->ast, pipe_struct);
		free(pipe_struct);
		free_ast(data->ast);
		free_main_exit(data, 1, 0);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
	read_pipe(data, pipe_struct);
	free(pipe_struct); // double free child process
	print_debugging_info_executer(INT_DEBUG, 2, NULL);
	printf("##########################################################\n");
	return (0);
}

static void	read_pipe(t_main_data *data, t_pipefd *pipe_struct)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int		i_count;

	i_count = 0;
	close(pipe_struct->pipefd[1]); // Schreibende schließen
	while ((bytes_read = read(pipe_struct->pipefd[0], buffer,
				sizeof(buffer))) > 0)
	{
		while (i_count < bytes_read)
		{
			env_add_clr(data, &buffer[i_count]);
			i_count += strlen(&buffer[i_count]) + 1;
		}
	}
	close(pipe_struct->pipefd[0]); 
}


static void	env_add_clr(t_main_data *data, char *env_var)
{
	if (ft_strncmp(env_var, ADD_ENV, ft_strlen(ADD_ENV)) == 0)
	{
		print_debugging_info_executer(INT_DEBUG, 20, env_var);
		env_set_var(data, env_var + ft_strlen(ADD_ENV));
	}
	else if (ft_strncmp(env_var, CLR_ENV, ft_strlen(CLR_ENV)) == 0)
	{
		print_debugging_info_executer(INT_DEBUG, 21, env_var);
	}
	else if (ft_strncmp(env_var, ADD_CD, ft_strlen(ADD_CD)) == 0)
	{
		print_debugging_info_executer(INT_DEBUG, 22, env_var);
		if (chdir(env_var + ft_strlen(ADD_CD) + 4) == -1)
			error_code_handler(errno, "ERR-chdir", "CD -Command --> ", env_var + ft_strlen(ADD_CD) + 4);
	}
}

