#include "minishell.h"

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
	int	exit_code;

	exit_code = 0;
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		return (exit_code);
	}
	else if (WIFSIGNALED(status))
	{
		ft_printf_fd(2, "piped\n");
		exit_code = WTERMSIG(status) + 128;
		if (exit_code == 130)
		{
			ft_printf("\n");
		}
		if (exit_code == 131)
		{
			ft_printf("Quit\n");
		}
		if (exit_code == SIGPIPE + 128)
			exit_code = 0;
	}
	return (exit_code);
}
