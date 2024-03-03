#include "minishell.h"

static int				signal_helper(int signals, int ign_or_dfl);
static __sighandler_t	get_correct_signal(int ign_or_dfl);
static int				init_struct_sigaction(struct sigaction *sa,
							int ign_or_dfl);

int	ignore_signals(int signals)
{
	if (signal_helper(signals, MY_SIG_IGNORE))
		return (1);
	return (0);
}

int	restore_default_signals(int signals)
{
	if (signal_helper(signals, MY_SIG_DEFAULT))
		return (1);
	return (0);
}

static int	signal_helper(int signals, int ign_or_dfl)
{
	struct sigaction	sa;

	init_struct_sigaction(&sa, ign_or_dfl);
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

static __sighandler_t	get_correct_signal(int ign_or_dfl)
{
	if (ign_or_dfl == MY_SIG_DEFAULT)
		return (SIG_DFL);
	else
		return (SIG_IGN);
}

static int	init_struct_sigaction(struct sigaction *sa, int ign_or_dfl)
{
	sigemptyset(&(sa->sa_mask));
	sa->sa_flags = 0;
	sa->sa_handler = get_correct_signal(ign_or_dfl);
	return (0);
}
