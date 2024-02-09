#include "minishell.h"

/**
 * @brief using the execve function
 *
 * @param exec struct for execve
 */
void	execve_handler(const char *file_path, char **argv, char **env)
{
	// if (access_handler(file_path, FILE_EXISTS) == 0)
	// {
		// filep = NULL
		if (execve(file_path, argv, env) == -1)
		{
			error_code_handler(errno, "ERR-execve", file_path, " ");
			exit(EXIT_FAILURE);
		}
	//}
	else
		printf("ERR-execve: (access-Error) No executable file path"
			"please check the path!");
}