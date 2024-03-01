#include "minishell.h"

void	execve_handler(const char *file_path, char **argv, char **env)
{
	if (execve(file_path, argv, env) < 0)
	{
		//printf("ernor nbr %i", errno);
	//	perror("ERR : EXECVE");
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_EXECVE,
			"function \"execve_handler\""});
		//throw_error_mimic_bash("ERRRRRRR", 12);
		exit(EXIT_FAILURE);
	}
}
