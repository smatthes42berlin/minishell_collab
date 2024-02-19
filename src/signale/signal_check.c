#include "minishell.h"

int	signal_setting(void);

int	signal_check(void)
{
	if (signal_setting() == -1)
		exit(EXIT_FAILURE);
	return (0);
}

int	error_setting(void)
{
	perror("Signalfunktion");
	// exit(EXIT_FAILURE);
	return (-1);
}

int	signal_setting(void)
{
	int ret;

	ret = 0;
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		ret = error_setting();
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		ret = error_setting();
	else
		ret = 1;
	return (ret);
}