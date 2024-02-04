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

	executor(&main_data);

	// printf("%s\n", env_get_var(&main_data, "OLDPWD"));
	// printf("%s\n", env_get_var(&main_data, "PWD"));
	// env_print(&main_data);
	// env_set_var(&main_data, "OLDPWD=Testttttttttttttttttttttttttttt");
	// env_set_var(&main_data, "PWD=Testttttttttttttttttttttttttttt");
	// printf("\n\n%s\n\n\n", env_get_var(&main_data, "OLDPWD"));
	// env_print(&main_data);

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
