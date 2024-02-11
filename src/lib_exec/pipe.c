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
void	pipe_setting(int *pipefd, bool open, char **str)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int		i_count;

	if (open)
	{
		int i_count; 

		i_count = 0;
		close(pipefd[0]);
	    if (str != NULL)
		{
			while (str[i_count] != NULL)
			{
				//printf("write in pipe :|%s|\n", str[i_count]);
				write(pipefd[1], str[i_count], ft_strlen(str[i_count]) + 1);
				i_count++;
			}
		}
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		if (str != NULL)
		{
			i_count = 0;	
			while ((bytes_read = read(pipefd[0], buffer,
							sizeof(buffer))) > 0)
			{
				while (i_count < bytes_read)
				{
					printf("%s", &buffer[i_count]);
					i_count += strlen(&buffer[i_count]) + 1;
				}
			}
		}
		close(pipefd[0]);
	}
}

