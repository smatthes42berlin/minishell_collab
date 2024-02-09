#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_main_data	main_data;
	char		*test_str;
	int			test_case;
	int			exit_code;

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
		// test_str = ft_strdup("< in_1 cat << 1 < in_2 | ls < in_3 | wc-l < in_4 > 2 | echo Hello");
		// test_str = ft_strdup("<< 1 echo || << 2 cat");
		// test_str = ft_strdup("echo");
		// test_str = ft_strdup("exit | echo | < 1.in >> 2.in cat arg_1 arg_2| << 1 echo arg1 < 2.in arg2 | <<1 wc
				// -l -s | ls < 2.in > 3.out");
		test_str = ft_strdup("<< 1 cat <in_1 | echo <in_2 hi | <in_3 wc > 2");
	if (test_case == 2)
		test_str = ft_strdup("<< >> < | >");
	if (test_case == 3)
		test_str = ft_strdup("cat << 1 > out | wc > out2");
	if (test_case == 4)
		test_str = ft_strdup("sleep 2 | echo hello | sleep 3 | echo 123");
	if (test_case == 5)
		test_str = ft_strdup("cat <<1<<2<<3");
	if (test_case == 6)
		test_str = ft_strdup("xxx$HOME$FIVE_ONE xxx>xxx$ONE_TWO $SOME_LETTERS $? $. $$ $; ?$_?");
	if (test_case == 7)
		test_str = ft_strdup("<< 1 << 2");
	if (test_case == 8)
		test_str = ft_strdup("sleep arg1 arg2 arg3");
	if (test_case == 9)
		test_str = ft_strdup("sleep 2 | sleep 2");
	if (test_case == 10)
		test_str = ft_strdup("< in_1 cat << 1 < in_2 | ls < in_3 |");
	printf("TESTCASE: %s\n", test_str);
	env_set_var(&main_data, "EMPTY=");
	env_set_var(&main_data, "FIVE_ONE=11111");
	env_set_var(&main_data, "ONE_TWO=2");
	env_set_var(&main_data, "SOME_LETTERS=asdfsdf");
	// env_print(&main_data);
	while (1)
	{
		// watch out for eof and possbile return of null
		main_data.cli_input = test_str;
		main_data.cli_input = readline("cli>");
		if (!main_data.cli_input || ft_strlen(main_data.cli_input) == 0)
			continue ;
		// free_main_exit(&main_data, 2, -1);
		add_history(main_data.cli_input);
		printf("main: before tokenise\n");
		if (tokenise(&main_data))
			free_main_exit(&main_data, 3, 2);
		printf("main: before expand\n");
		if (expand(&main_data))
			free_main_exit(&main_data, 3, 3);
		printf("main: before parse\n");
		// print_token_list(main_data.token_list);
		exit_code = parse(&main_data);
		printf("\n\nEXIT CODE = $%d$\n\n", exit_code);
		if (exit_code)
		{
			free_main_exit(&main_data, 3, 4);
		}
		if (executor(&main_data) == -1)
			return (3);
		// free_main_exit(&main_data, 3, 0);
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
