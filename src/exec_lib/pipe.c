#include "minishell.h"

/**
 * @brief creat a pipe and check for errors
 * 
 * @param pipefd 
 */
void	pipe_handler(int *pipefd)
{
	if (pipe(pipefd) < 0)
		error_code_handler(errno, "ERR-pipe", " ", " ");
}

/**
 * @brief set the given pipefild for close or open
 * 
 * @param pipefd arry of [2]
 * @param open if true the pipe is open
 */
void	pipe_setting(int *pipefd, bool open)
{
	if (open)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}