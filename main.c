#include "minishell.h"

volatile enum e_systemstate systemstate = STATE_IDLE;

void signal_handler(int sig) {
    if (sig == SIGINT) 
	{
        systemstate = STATE_SIGINT;
        printf("\nSIGINT empfangen, drücke nochmals Ctrl+C\n");
		//signal(SIGINT, SIG_IGN);
    }
	if (sig == SIGQUIT) 
	{
        systemstate = STATE_SIGQUIT;
         printf("\nSIGINT empfangen, drücke nochmals Ctrl+\\\n");
    }
	if (sig == 1000) 
	{
        systemstate = STATE_EOF;
         printf("\nSIGINT empfangen, drücke nochmals Ctrl+D\n");
    }
}

int	main(int argc, char *argv[], char *envp[])
{
	t_main_data	main_data;
	char		*test_str;
	int			exit_code;

	if (argc > 1)
	{
		printf("Error: program '%s' doesn't take any arguments!", argv[0]);
		return (1);
	}

	if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }
	if (signal(SIGQUIT, signal_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

	init_main_data(&main_data);
	if (init_env_vars(&main_data, envp))
		return (1);
	test_str = get_test_case(12);
	printf("TESTCASE: %s\n", test_str);
	env_set_var(&main_data, "EMPTY=");
	env_set_var(&main_data, "FIVE_ONE=11111");
	env_set_var(&main_data, "ONE_TWO=2");
	env_set_var(&main_data, "SOME_LETTERS=asdfsdf");
	// env_print(&main_data);
	while (1)
	{
		main_data.cli_input = test_str;
		main_data.cli_input = readline("cli>");
		if (!main_data.cli_input)
		{
			free_main_exit(&main_data, 2, 1);
			signal_handler(1000);
		}
		if (ft_strlen(main_data.cli_input) == 0)
			continue;
		printf("main: before tokenise\n");
		if (tokenise(&main_data))
			free_main_exit(&main_data, 2);
		printf("main: before expand\n");
		if (expand(&main_data))
			free_main_exit(&main_data, 3);
		printf("main: before parse\n");
		// //print_token_list(main_data.token_list);
		// // write heredocs to pipe here
		exit_code = parse(&main_data);
		printf("\n\nEXIT CODE = $%d$\n\n", exit_code);
		if (exit_code)
		{
			free_main_exit(&main_data, 4);
		}
		if (executor(&main_data) == -1)
			return (3);
		//free_main_exit(&main_data, 3, 0);
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

static char	*get_test_case(int test_case)
{
	if (test_case == 1)
		return (ft_strdup("<< 1 cat <in_1 | echo <in_2 hi | <in_3 wc > 2"));
	if (test_case == 2)
		return (ft_strdup("<< >> < | >"));
	if (test_case == 3)
		return (ft_strdup("cat << 1 > out | wc > out2"));
	if (test_case == 4)
		return (ft_strdup("sleep 2 | echo hello | sleep 3 | echo 123"));
	if (test_case == 5)
		return (ft_strdup("cat <<1<<2<<3"));
	if (test_case == 6)
		return (ft_strdup("xxx$HOME$FIVE_ONE xxx>xxx$ONE_TWO $SOME_LETTERS $? $. $$ $); ?$_?"));
	if (test_case == 7)
		return (ft_strdup("<< 1 << 2"));
	if (test_case == 8)
		return (ft_strdup("sleep arg1 arg2 arg3"));
	if (test_case == 9)
		return (ft_strdup("sleep 2 | sleep 2"));
	if (test_case == 10)
		return (ft_strdup("< in_1 cat << 1 < in_2 | ls < in_3 |"));
	if (test_case == 11)
		return (ft_strdup("$HOME \"$HOME\" '$HOME' \"\" '' $HOME $HOME1"));
	if (test_case == 12)
		return (ft_strdup("<< 1 cat"));
	return (NULL);
}
