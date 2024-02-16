#include "minishell.h"

char	*get_failed_func_str_1(enum e_failed_func failed_func)
{
	if (failed_func == EFUNC_RL_CLEAR_HISTORY)
		return ("RL_CLEAR_HISTORY");
	if (failed_func == EFUNC_RL_ON_NEW_LINE)
		return ("RL_ON_NEW_LINE");
	if (failed_func == EFUNC_RL_REPLACE_LINE)
		return ("RL_REPLACE_LINE");
	if (failed_func == EFUNC_RL_REDISPLAY)
		return ("RL_REDISPLAY");
	if (failed_func == EFUNC_ADD_HISTORY)
		return ("ADD_HISTORY");
	if (failed_func == EFUNC_PRINTF)
		return ("PRINTF");
	if (failed_func == EFUNC_MALLOC)
		return ("MALLOC");
	if (failed_func == EFUNC_FREE)
		return ("FREE");
	if (failed_func == EFUNC_WRITE)
		return ("WRITE");
	if (failed_func == EFUNC_ACCESS)
		return ("ACCESS");
	if (failed_func == EFUNC_OPEN)
		return ("OPEN");
	if (failed_func == EFUNC_READ)
		return ("READ");
	return (get_failed_func_str_2(failed_func));
}
char	*get_failed_func_str_2(enum e_failed_func failed_func)
{
	if (failed_func == EFUNC_CLOSE)
		return ("CLOSE");
	if (failed_func == EFUNC_FORK)
		return ("FORK");
	if (failed_func == EFUNC_WAIT)
		return ("WAIT");
	if (failed_func == EFUNC_WAITPID)
		return ("WAITPID");
	if (failed_func == EFUNC_WAIT3)
		return ("WAIT3");
	if (failed_func == EFUNC_WAIT4)
		return ("WAIT4");
	if (failed_func == EFUNC_SIGNAL)
		return ("SIGNAL");
	if (failed_func == EFUNC_SIGACTION)
		return ("SIGACTION");
	if (failed_func == EFUNC_SIGEMPTYSET)
		return ("SIGEMPTYSET");
	if (failed_func == EFUNC_SIGADDSET)
		return ("SIGADDSET");
	if (failed_func == EFUNC_KILL)
		return ("KILL");
	if (failed_func == EFUNC_EXIT)
		return ("EXIT");
	return (get_failed_func_str_3(failed_func));
}

char	*get_failed_func_str_3(enum e_failed_func failed_func)
{
	if (failed_func == EFUNC_GETCWD)
		return ("GETCWD");
	if (failed_func == EFUNC_CHDIR)
		return ("CHDIR");
	if (failed_func == EFUNC_STAT)
		return ("STAT");
	if (failed_func == EFUNC_LSTAT)
		return ("LSTAT");
	if (failed_func == EFUNC_FSTAT)
		return ("FSTAT");
	if (failed_func == EFUNC_UNLINK)
		return ("UNLINK");
	if (failed_func == EFUNC_EXECVE)
		return ("EXECVE");
	if (failed_func == EFUNC_DUP)
		return ("DUP");
	if (failed_func == EFUNC_DUP2)
		return ("DUP2");
	if (failed_func == EFUNC_PIPE)
		return ("PIPE");
	if (failed_func == EFUNC_OPENDIR)
		return ("OPENDIR");
	if (failed_func == EFUNC_READDIR)
		return ("READDIR");
	return (get_failed_func_str_4(failed_func));
}

char	*get_failed_func_str_4(enum e_failed_func failed_func)
{
	if (failed_func == EFUNC_CLOSEDIR)
		return ("CLOSEDIR");
	if (failed_func == EFUNC_STRERROR)
		return ("STRERROR");
	if (failed_func == EFUNC_PERROR)
		return ("PERROR");
	if (failed_func == EFUNC_ISATTY)
		return ("ISATTY");
	if (failed_func == EFUNC_TTYNAME)
		return ("TTYNAME");
	if (failed_func == EFUNC_TTYSLOT)
		return ("TTYSLOT");
	if (failed_func == EFUNC_IOCTL)
		return ("IOCTL");
	if (failed_func == EFUNC_GETENV)
		return ("GETENV");
	if (failed_func == EFUNC_TCSETATTR)
		return ("TCSETATTR");
	if (failed_func == EFUNC_TCGETATTR)
		return ("TCGETATTR");
	if (failed_func == EFUNC_TGETENT)
		return ("TGETENT");
	if (failed_func == EFUNC_TGETFLAG)
		return ("TGETFLAG");
	return (get_failed_func_str_5(failed_func));
}

char	*get_failed_func_str_5(enum e_failed_func failed_func)
{
	if (failed_func == EFUNC_TGETNUM)
		return ("TGETNUM");
	if (failed_func == EFUNC_TGETSTR)
		return ("TGETSTR");
	if (failed_func == EFUNC_TGOTO)
		return ("TGOTO");
	if (failed_func == EFUNC_TPUTS)
		return ("TPUTS");
	return (NULL);
}
