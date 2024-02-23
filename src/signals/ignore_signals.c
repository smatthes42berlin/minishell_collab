#include "minishell.h"

int	ignore_signals(int signals)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	if (signals == SIGINT)
	{
		if (sigaction(SIGINT, &sa, NULL))
			return (throw_error_custom((t_error_ms){errno, EPART_SIGNAL,
					EFUNC_SIGACTION, "ignoring SIGINT"}));
	}
	if (signals == SIGQUIT)
	{
		if (sigaction(SIGQUIT, &sa, NULL))
			return (throw_error_custom((t_error_ms){errno, EPART_SIGNAL,
					EFUNC_SIGACTION, "ignoring SIGQUIT"}));
	}
	if (signals == SIGINT + SIGQUIT)
	{
		if (sigaction(SIGINT, &sa, NULL))
			return (throw_error_custom((t_error_ms){errno, EPART_SIGNAL,
					EFUNC_SIGACTION, "ignoring SIGINT"}));
		if (sigaction(SIGQUIT, &sa, NULL))
			return (throw_error_custom((t_error_ms){errno, EPART_SIGNAL,
					EFUNC_SIGACTION, "ignoring SIGQUIT"}));
	}
	return (0);
}
