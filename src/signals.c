#include "minishell.h"

// ctrl + D -> EOF -> closes stdin pipe
// ctrl + \ -> QUIT -> SIGQUIT 3
// ctrl + C -> INTERUPT -> SIGINT 2

// in interactive mode
// ctrl + D -> exit shell
// ctrl + C -> newline
// ctrl + \ -> does

bool	only_newline_entered(t_main_data *main_data)
{
	if (ft_strlen(main_data->cli_input) == 0)
		return (true);
	return (false);
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

void	handle_sigquit(int sig)
{
	printf("quit: %d!\n", sig);
}

void	handle_sigint(int sig)
{
	printf("int: %d!\n", sig);
}

void	signal_main(void)
{
	struct sigaction sa;

	sa.sa_handler = &handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = &handle_sigint;
	sigaction(SIGINT, &sa, NULL);
}