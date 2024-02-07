#include "minishell.h"

static void read_pipe(t_main_data *data, t_pipefd *pipe_struct);
static void env_add_clr(t_main_data *data, char *env_var);

t_node	*example_selection(void)
{
	t_node	*ret;

	// ret = set_cmd_1();							// ls -l;
	// ret = set_cmd_2();  					// ls -l | grep ".c"
	// ret = set_cmd_2_cp();					// pwd | ls -l
	// ret = set_cmd_3();						// sleep 2 | ls -l | wc -l
	 ret = set_cmd_4();						// sleep 2 | ls -l | grep ".c" | sort -r
	
	// ret = set_redir_in_1();					// < input grep "nn" 
	// ret = set_redir_in_1_cmd_2();			// < input grep "nn" | uniq | sort 
	// ret = set_redir_in_2_cmd_2();			// < input_befor < input grep "nn" | sort | uniq	
	// ret = set_redir_out_1_append();			// ls -l >> out 
	// ret = set_redir_out_1();					// ls -l > out 
	
	// ---------------------------------------- build pwd -----
	// ret = set_pwd_allone(); 					// pwd
	// ret = set_pwd_beginn_1(); 					// pwd | grep home
	// ret = set_pwd_begin_2(); 				// pwd | ls -l
	// ret = set_pwd_end(); 					// ls -l | pwd
	// ret = set_pwd_redir_out(); 				// pwd > out

	// --------------------------------------- build cd ------
 	// ret = set_cd_absolut();
	// ret = set_cd_relativ();
	// ret = set_cd_relativ_revers();
	return (ret);
	// Maybe test case 
// sleep |  < input grep "nn" | uniq | sort -r 

}

void	executor(t_main_data *data)
{
	pid_t	pid;
	int 	pipefd[2];
	t_pipefd 	*pipe_struct;

	pipe_handler(pipefd);
	pipe_struct = malloc_handler(sizeof(t_pipefd));
	pipe_struct->pipefd = pipefd;
	pid = fork_handler();
	if (pid == 0)
	{
		if (data->ast == NULL)
			data->ast = example_selection();
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

	// printf("\n\n  PWD : %s\n", env_get_var(data, "PWD"));
	// printf(" OPLDPD : %s\n", env_get_var(data, "OLDPWD"));
}


static void read_pipe(t_main_data *data, t_pipefd *pipe_struct)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
	int i_count;

	i_count = 0;
	close(pipe_struct->pipefd[1]); // Schreibende schließen
    while ((bytes_read = read(pipe_struct->pipefd[0], buffer, sizeof(buffer))) > 0) {
            // Annahme: BUFFER_SIZE reicht aus, um jede Umgebungsvariable komplett zu lesen
            // In der Praxis müssten Sie möglicherweise die Daten in Schleifen lesen und zusammensetzen
        while (i_count < bytes_read)
		{
			env_add_clr(data, &buffer[i_count]);
            //printf("Empfangen: %s\n", &buffer[i_count]);
            i_count += strlen(&buffer[i_count]) + 1;
		}
    }
    close(pipe_struct->pipefd[0]); // Leseende schließen
	//printf("OLDPWD ---- %s\n", env_get_var(data, "OLDPWD"));
	//printf("   PWD ---- %s\n", env_get_var(data, "PWD"));
}
static void env_add_clr(t_main_data *data, char *env_var)
{
	if (ft_strncmp(env_var, ADD_ENV, ft_strlen(ADD_ENV)) == 0)
	{
		env_set_var(data, env_var + ft_strlen(ADD_ENV));
		// printf("i found ADD -->  %s\n", env_var + ft_strlen(ADD_ENV));
	}
	else if (ft_strncmp(env_var, CLR_ENV, ft_strlen(CLR_ENV)) == 0)
	{
		printf("i found CLEAR -->  %s\n", env_var + ft_strlen(CLR_ENV));
	}
}
