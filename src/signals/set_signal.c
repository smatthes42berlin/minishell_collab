#include "minishell.h"

int	set_signal(int signal, void (*func)(int))
{
	struct sigaction	sa;

	sa.sa_handler = func;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(signal, &sa, NULL))
		return (throw_error_custom((t_error_ms){errno, EPART_SIGNAL,
				EFUNC_SIGACTION, "setting signal"}));
	return (0);
}
