#include "minishell.h"

// static void	write_pipe(int *pipefd, char **str, char *error_msg);
// static void read_pipe(int *pipefd, char **str, char *error_msg);

/**
 * @brief creat a pipe and check for errors
 *
 * @param pipefd
 */
void	pipe_handler(int *pipefd, char *str)
{
	if (pipe(pipefd) < 0)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_PIPE,
			str});
}

void	pipe_setting_exit_code(int *pipefd, bool open, int *exit_code,
	char *error_msg)
{
	if (open == true)
	{
		use_close(pipefd[0], error_msg);
		if (write(pipefd[1], exit_code, sizeof(*exit_code)) < 0)
			throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_WRITE,
				error_msg});
		use_close(pipefd[1], error_msg);
	}
	else
	{
		use_close(pipefd[1], error_msg);
		if (read(pipefd[0], exit_code, sizeof(*exit_code)) < 0)
			throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_READ,
				error_msg});
		use_close(pipefd[0], error_msg);
	}
	
}

