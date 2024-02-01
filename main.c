#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_main_data	main_data;
	char		*test_str;
	int			test_case;

	if (argc > 1)
	{
		printf("Error: program '%s' doesn't take any arguments!", argv[0]);
		return (1);
	}
	init_main_data(&main_data);
	if (init_env_vars(&main_data, envp))
		return (1);
	test_case = 1;
	if (test_case == 1)
		test_str = ft_strdup("cat << 1 | ls | wc -l > 2");
	if (test_case == 2)
		test_str = ft_strdup("<< >> < | >");
	if (test_case == 3)
		test_str = ft_strdup("cat << 1 > out | wc > out2");
	if (test_case == 4)
		test_str = ft_strdup("sleep 2 | echo hello | sleep 3 | echo 123");
	if (test_case == 5)
		test_str = ft_strdup("cat <<1<<2<<3");
	printf("TESTCASE: %s\n", test_str);
	env_print(&main_data);
	while (1)
	{
		// watch out for eof and possbile return of null
		// main_data.cli_input = readline("cli>");
		main_data.cli_input = test_str;
		if (!main_data.cli_input || ft_strlen(main_data.cli_input) == 0)
			free_main_exit(&main_data, 2, 1);
		if (tokenise(&main_data))
			free_main_exit(&main_data, 3, 1);
		if (expand(&main_data))
			free_main_exit(&main_data, 3, 1);
		print_token_list(main_data.token_list);
		free_main_exit(&main_data, 3, 0);
		// if (parse(&main_data) == -1)
		// 	return (2);
		// // - (Check if inbuilts that change main process, e.g. cd)
		// // if (execute(main_data) == -1)
		// // 	return (3);
		// d_lst_clear(&main_data.token_list, free);
	}
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
