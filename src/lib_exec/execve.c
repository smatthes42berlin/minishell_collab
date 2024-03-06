#include "minishell.h"

int	execve_handler(const char *file_path, char **argv, char **env)
{
	if (execve(file_path, argv, env) < 0)
	{
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_EXECVE,
			"function \"execve_handler\""});
		return (-1);
	}
	return (0);
}
