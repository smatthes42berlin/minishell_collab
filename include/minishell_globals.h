// globals.h
#ifndef MINISHELL_GLOBALS_H
# define MINISHELL_GLOBALS_H

enum								e_systemstate
{
	STATE_IDLE,
	STATE_RUNNING,
	STATE_PAUSED,
	STATE_STOPPED,
	STATE_SIGINT,
	STATE_SIGQUIT,
	STATE_EOF
};

extern volatile enum e_systemstate	systemstate;

#endif
