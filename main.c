#include "minishell.h"

static int	start_minishell(t_main_data *main_data);
static int	read_line_handle_signals(t_main_data *main_data);
static int	handle_sigint_main(int ret_tokenise);
static int	handle_one_prompt(t_main_data *main_data, int ret_tokenise);

int	main(int argc, char *argv[], char *envp[])
{
	t_main_data	*main_data;

	main_data = get_main_data();
	if (TEST_MODE)
	{
		main_data->cli_input = ft_strdup(argv[2]);
	}
	else
	{
		if (check_num_args(argc, argv))
			return (1);
	}
	if (init_env_vars(main_data, envp))
		free_main_exit(main_data, 1);
	return (start_minishell(main_data));
}

static int	start_minishell(t_main_data *main_data)
{
	int	res;

	while (1)
	{
		res = handle_one_prompt(main_data, 0);
		if (TEST_MODE)
			free_main_exit(main_data, -1);
		if (res == CONTINUE)
		{
			free_main_exit_end_of_loop(main_data);
			continue ;
		}
		else
		{
			free_main_exit(main_data, -1);
		}
	}
	return (0);
}

static int	handle_one_prompt(t_main_data *main_data, int ret_tokenise)
{
	int	tmp;

	ret_tokenise++;
	if (read_line_handle_signals(main_data))
		return (QUIT);
	if (no_input(main_data))
		return (CONTINUE);
	add_history(main_data->cli_input);
	ret_tokenise = tokenise(main_data);
	if (handle_sigint_main(ret_tokenise))
		return (CONTINUE);
	if (ret_tokenise)
		return (CONTINUE);
	if (expand(main_data))
		return (QUIT);
	tmp = token_lst_is_empty(main_data);
	if (tmp == -1)
		return (QUIT);
	if (tmp == 1)
		return (CONTINUE);
	if (parse(main_data))
		return (QUIT);
	if (executor(main_data) == -1)
		return (QUIT);
	return (CONTINUE);
}

static int	read_line_handle_signals(t_main_data *main_data)
{
	if (start_signals_interactive())
		return (QUIT);
	read_line(main_data);
	if (end_signals_interactive())
		return (QUIT);
	if (check_ctrl_d(main_data))
		return (QUIT);
	return (0);
}

static int	handle_sigint_main(int ret_tokenise)
{
	if (ret_tokenise == SIGINT + 128)
	{
		handle_heredoc_was_ctrl_c(128 + SIGINT);
		return (CONTINUE);
	}
	return (0);
}
