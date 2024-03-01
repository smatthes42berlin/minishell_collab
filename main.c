#include "minishell.h"

static int	start_minishell(t_main_data *main_data, int ret_tokenise);
static int	read_line_handle_signals(t_main_data *main_data);
static int	handle_sigint_main(t_main_data *main_data, int ret_tokenise);

int	main(int argc, char *argv[], char *envp[])
{
	t_main_data	*main_data;

	if (check_num_args(argc, argv))
		return (1);
	main_data = get_main_data();
	if (init_env_vars(main_data, envp))
		return (1);
	return (start_minishell(main_data, 0));
}

static int	start_minishell(t_main_data *main_data, int ret_tokenise)
{
	while (1)
	{
		if (read_line_handle_signals(main_data))
			free_main_exit(main_data, 1);
		if (only_newline_entered(main_data))
			continue ;
		add_history(main_data->cli_input);
		ret_tokenise = tokenise(main_data);
		if (handle_sigint_main(main_data, ret_tokenise))
			continue ;
		if (ret_tokenise)
			free_main_exit(main_data, 1);
		if (expand(main_data))
			free_main_exit(main_data, 1);
		if (parse(main_data))
			free_main_exit(main_data, 1);
		if (executor(main_data) == -1)
			free_main_exit(main_data, 1);
		//free_main_exit(main_data, 1);
		free_main_exit_end_of_loop(main_data);
	}
	return (0);
}

static int	read_line_handle_signals(t_main_data *main_data)
{
	if (start_signals_interactive())
		free_main_exit(main_data, 1);
	read_line(main_data);
	if (end_signals_interactive())
		free_main_exit(main_data, 1);
	if (check_ctrl_d(main_data))
		free_main_exit(main_data, 1);
	return (0);
}

static int	handle_sigint_main(t_main_data *main_data, int ret_tokenise)
{
	if (ret_tokenise == SIGINT + 128)
	{
		handle_heredoc_was_ctrl_c(128 + SIGINT);
		free_main_exit_end_of_loop(main_data);
		return (1);
	}
	return (0);
}
