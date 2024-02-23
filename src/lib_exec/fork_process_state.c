#include "minishell.h"

/**
 * @brief fork a Process and check for Error if fork failed
 *
 * @return pid_t
 */
pid_t	fork_handler(char *str)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_PIPE,
			str});
	return (pid);
}

int	get_process_exit_code(int status)
{
	//int	temp_sig;
	int	exit_code;

	exit_code = 0;
	if (WIFEXITED(status))
	{
       exit_code = WEXITSTATUS(status);
    }
	// printf("exitcode ist |%i|\n", exit_code);
	// if (WIFEXITED(status))
	// 	exit_code = 0;
	// else if (WIFSIGNALED(status))
	// {
	// 	temp_sig = WTERMSIG(status);
	// 	exit_code = 128 + temp_sig;
	// 	if (WCOREDUMP(status))
	// 		exit_code = 6;
	// }
	// else if (WIFSTOPPED(status))
	// 	exit_code = 21;
	// else if (WIFCONTINUED(status))
	// 	exit_code = 22;
	return (exit_code);
}

// enum e_process_status	evaluate_process_status(int status)
// {
// 	int	temp_sig;

// 	if (WIFEXITED(status))
// 		return (PROCESS_EXITED);
// 	else if (WIFSIGNALED(status))
// 	{
// 		temp_sig = WTERMSIG(status);
		//if (SIGINT == temp_sig)
// 			return (PROCESS_KILLED_BY_SIGINT);
// 		else if (SIGSEGV == temp_sig)
// 			return (PROCESS_KILLED_BY_SIGSEGV);
// 		else if (SIGTERM == temp_sig)
// 			return (PROCESS_KILLED_BY_SIGTERM);
// 		else if (SIGQUIT == temp_sig)
// 			return (PROCESS_KILLED_BY_SIGQUIT);
// 		else
// 			return (PROCESS_KILLED_OTHER);
// 	}
// 	else if (WIFSTOPPED(status))
// 		return (PROCESS_STOPPED);
// 	else if (WIFCONTINUED(status))
// 		return (PROCESS_CONTINUED);
// 	return (PROCESS_EXITED);
// }
