#include "minishell.h"
int	main(int argc, char *argv[], char *envp[])
{
	t_main_data	main_data;

	if (*envp[0] == 'f')
		printf("Noting\n");

	if (argc > 1)
	{
		printf("Error: program '%s' doesn't take any arguments!", argv[0]);
		return (1);
	}
	 init_main_data(&main_data);
	if (init_env_vars(&main_data, envp))
		return (1);
	printf("---------------------TESTCASE:--------------\n\n");

	executor();

	printf("\n\n----------------------------------\n\n");

	free_main_exit(&main_data, 1, 0);
	return (0);
}


int	init_main_data(t_main_data *main_data)
{
	main_data->ast = NULL;
	main_data->cli_input = NULL;
	main_data->env_vars = NULL;
	main_data->token_list = NULL;
	main_data->env_vars = NULL;
	return (0);
}
