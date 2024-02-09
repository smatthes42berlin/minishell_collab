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
 * @param str str is for the is_inbuilt's function
 */
void	pipe_setting(int *pipefd, bool open, char *str)
{
	if (open)
	{
		close(pipefd[0]);

	    if (str != NULL)
            write(pipefd[1], str, ft_strlen(str));
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		if (str != NULL)
			printf("%s\n", str);
		// Lesen und Ausgabe des Inhalts aus der Pipe
			// char buffer[1024];
			// ssize_t bytesRead;
			// printf("----------Reding from PIPE-----------\n");
			// while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
			// 	write(STDOUT_FILENO, buffer, bytesRead);
			// }
			// printf("----------End of PIPE READING-----------\n");
		////////////////////////////////////
		close(pipefd[0]);
	}
}