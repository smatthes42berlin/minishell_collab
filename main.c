#include "minishell.h"

// static char	*get_test_case(int test_case);

int	main(int argc, char *argv[], char *envp[])
{
	t_main_data	*main_data;
	int			exit_code;

	// char		*test_str;
	if (argc > 1)
	{
		printf("Error: program '%s' doesn't take any arguments!", argv[0]);
		return (1);
	}
	main_data = get_main_data();
	if (init_env_vars(main_data, envp))
		return (1);
	// test_str = get_test_case(1);
	// printf("TESTCASE: %s\n", test_str);
	env_set_var(main_data, "EMPTY=");
	env_set_var(main_data, "FIVE_ONE=11111");
	env_set_var(main_data, "ONE_TWO=2");
	env_set_var(main_data, "SOME_LETTERS=asdfsdf");
	// env_print(&main_data);
	while (1)
	{
		start_signals_interactive();
		// main_data->cli_input = test_str;
		main_data->cli_input = readline("cli>");
		if (check_ctrl_d(main_data))
			free_main_exit(main_data, 1);
		main_data->num_lines++;
		if (only_newline_entered(main_data))
			continue ;
		// printf("line %s\n", main_data->cli_input);
		add_history(main_data->cli_input);
		// printf("main: before tokenise\n");
		if (tokenise(main_data))
			free_main_exit(main_data, 2);
		// printf("main: before expand\n");
		if (expand(main_data))
			free_main_exit(main_data, 3);
		// printf("main: before parse\n");
		if (PRINT_DEBUG_1)
			print_token_list(main_data->token_list);
		exit_code = parse(main_data);
		// printf("\n\nEXIT CODE = $%d$\n\n", exit_code);
		if (exit_code)
		{
			free_main_exit(main_data, 4);
			// printf("aaaa\n");
		}
		if (executor(main_data) == -1)
			return (3);
		// free_main_exit(main_data, 0);
	}
	return (0);
}

int	reset_main_data(t_main_data *main_data)
{
	main_data->ast = NULL;
	main_data->cli_input = NULL;
	main_data->env_vars = NULL;
	main_data->token_list = NULL;
	return (0);
}

t_main_data	*get_main_data(void)
{
	static t_main_data	data = {NULL, NULL, NULL, NULL, 0};

	return (&data);
}

// static char	*get_test_case(int test_case)
// {
// 	if (test_case == 1)
// 		return (ft_strdup("<< 1 cat <in_1 hello | echo -e
				// -s <in_2 hi | <in_3 wc-l > 2"));
// 	if (test_case == 2)
// 		return (ft_strdup("<< >> < | >"));
// 	if (test_case == 3)
// 		return (ft_strdup("cat << 1 > out | wc > out2"));
// 	if (test_case == 4)
// 		return (ft_strdup("sleep 2 | echo hello | sleep 3 | echo 123"));
// 	if (test_case == 5)
// 		return (ft_strdup("cat <<1<<2<<3"));
// 	if (test_case == 6)
// 		return (ft_strdup("xxx$HOME$FIVE_ONE xxx>xxx$ONE_TWO $SOME_LETTERS $? $. $$ $); ?$_?"));
// 	if (test_case == 7)
// 		return (ft_strdup("<< 1 << 2"));
// 	if (test_case == 8)
// 		return (ft_strdup("sleep arg1 arg2 arg3"));
// 	if (test_case == 9)
// 		return (ft_strdup("sleep 2 | sleep 2"));
// 	if (test_case == 10)
// 		return (ft_strdup("< in_1 cat << 1 < in_2 | ls < in_3 |"));
// 	if (test_case == 11)
// 		return (ft_strdup("$HOME \"$HOME\" '$HOME' \"\" '' $HOME $HOME1"));
// 	if (test_case == 12)
// 		return (ft_strdup("<< 1 cat"));
// 	return (NULL);
// }
