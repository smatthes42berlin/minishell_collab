#include "minishell.h"

/**
 * @brief using the execve function
 *
 * @param exec struct for execve
 */
void	execve_handler(const char *file_path, char **argv, char **env)
{
	if (execve(file_path, argv, env) < 0)
	{
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_ACCESS,
			"function \"access_handler\""});
	}
}