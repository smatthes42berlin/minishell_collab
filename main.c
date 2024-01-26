#include "minishell.h"

/**
 * main function and entry point into shell
 * first initialise the main_data structure to mostly NULL

	* then set up all the environment variables coming from main parameter envp and determined via system calls
 * then listen to line input in infinite loop
 * when line entered
 * tokenise the line
 * parse the token list
	* check,if calls are in builts that change main process and must thus be called inside of it
    * execute the ast
 * @param main_data data structure,
	that contains all the necessary data for the shell and gets passed around
*/
int	main(void)
{
	t_main_data	main_data;
	char		*test_str;
	int			test_case;

	init_main_data(&main_data);
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
	// - set up and handle environment
	// expand variables
	printf("%s\n", test_str);
	while (1)
	{
		// watch out for eof and possbile return of null
		main_data.cli_input = readline("cli>");
		// main_data.cli_input = test_str;
		if (!main_data.cli_input || ft_strlen(main_data.cli_input) == 0)
			free_main_exit(&main_data, 1, 1);
		if (tokenise(&main_data))
			free_main_exit(&main_data, 2, 1);
		print_token_list(main_data.token_list);
		free_main_exit(&main_data, 2, 0);
		// if (parse(&main_data) == -1)
		// 	return (2);
		// // - (Check if inbuilts that change main process, e.g. cd)
		// // if (execute(main_data) == -1)
		// // 	return (3);
		// d_lst_clear(&main_data.token_list, free);
	}
	return (0);
}

void	init_main_data(t_main_data *main_data)
{
	main_data->ast = NULL;
	main_data->cli_input = NULL;
	main_data->env_vars = NULL;
	main_data->token_list = NULL;
}

// int	main(void)
// {
// 	char *t_1 = "1 ";
// 	char *t_2 = "2 ";
// 	char *t_3 = "3\n";

// 	char *res;

// 	int test;

// 	test = ft_join_n_str(&res, 3, t_1, t_2, t_3); 
// 	printf("$%d$\n", test);
// 	printf("$%s$\n", res);
// 	free(res);
// 	return (1);
// }
