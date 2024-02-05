#include "minishell.h"

t_node	*example_selection(void)
{
	t_node	*ret;

	// ret = set_cmd_1();
	//  ret = set_cmd_2();
	// ret = set_cmd_2_cp();
	// ret = set_cmd_3();
	ret = set_cmd_4();
	// ret = set_redir_in_1();
	// ret = set_redir_in_1_cmd_2();
	// ret = set_redir_in_2_cmd_2();
	// ret = set_redir_out_1();
	// ---- build pwd -----
	// ret = set_pwd_allone(); // pwd
	// ret = set_pwd_beginn_1(); // pwd | grep home
	// ret = set_pwd_begin_2(); // pwd | ls -l
	// ret = set_pwd_end(); // ls -l | pwd
	// ret = set_pwd_redir_out(); ///pwd > out
	// ---- build cd
	 //ret = set_cd_absolut();
	 //ret = set_cd_relativ();
	// ret = set_cd_relativ_revers();
	return (ret);
}

void	executor(t_main_data *data)
{
	pid_t	pid;
	int 	pipefd[2];
	t_pipefd 	*pipe_struct;

	pipe_struct = malloc(sizeof(t_pipefd));
	// printf("%s\n", env_get_var(data, "OLDPWD"));
	// printf("%s\n-----------------------\n", env_get_var(data, "PWD"));
	pipe_handler(pipefd);
	pipe_struct->pipefd = pipefd;
	pid = fork_handler();
	if (pid == 0)
	{
		if (data->ast == NULL)
			data->ast = example_selection();
		navigate_tree_forward(data, data->ast, pipe_struct);
		free_ast(data->ast);
		exit(0);
	}
	else
	{
		//env_set_var(data, "PWD=Testttttttttttttttttttttttttttt");
		waitpid(pid, NULL, 0);
	}
	// printf("%s\n", env_get_var(data, "OLDPWD"));
	// printf("%s\n", env_get_var(data, "PWD"));

	env_print(data);
}
