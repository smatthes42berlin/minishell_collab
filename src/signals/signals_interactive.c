#include "minishell.h"

void	handle_ctrl_c_sigint_interactive(int signum)
{
	signum++;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (set_exit_code(130))
		throw_error_custom((t_error_ms){errno, EPART_SIGNAL, EFUNC_MALLOC,
			"set exit code on sigint"});
}

int	start_signals_interactive(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &handle_ctrl_c_sigint_interactive;
	if (sigaction(SIGINT, &sa, NULL))
		return (throw_error_custom((t_error_ms){errno, EPART_SIGNAL,
				EFUNC_SIGACTION, "starting SIGINT interactive mode"}));
	if (ignore_signals(SIGQUIT))
		return (1);
	return (0);
}

int	end_signals_interactive(void)
{
	if (ignore_signals(SIGINT))
		return (1);
	return (0);
}

int	check_ctrl_d(t_main_data *main_data)
{
	if (pressed_ctrl_d(main_data->cli_input))
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}
