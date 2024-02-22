#include "minishell.h"

static void	write_pipe(int *pipefd, char **str, char *error_msg);
static void read_pipe(int *pipefd, char **str, char *error_msg);

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

/**
 * @brief set the given pipefild for close or open
 *
 * @param pipefd arry of [2]
 * @param open if true the pipe is open
 * @param str str is for the is_inbuilt's function
 */
void	pipe_setting(int *pipefd, bool open, char **str, char *error_msg)
{
	if (open)
	{
		write_pipe(pipefd, str, error_msg);
	}
	else
	{
		read_pipe(pipefd, str, error_msg);
	}
}

void	pipe_setting_exit_code(int *pipefd, bool open, int *exit_code, char *error_msg)
{
	if (open)
	{
		use_close(pipefd[0], error_msg);
		write(pipefd[1], exit_code, sizeof(*exit_code)); 
		use_close(pipefd[1], error_msg);
	}
	else
	{
		use_close(pipefd[1], error_msg);
		read(pipefd[0], exit_code, sizeof(*exit_code));
		use_close(pipefd[0], error_msg);
	}
}

static void	write_pipe(int *pipefd, char **str, char *error_msg)
{
	int	i_count;

	i_count = 0;
	use_close(pipefd[0], error_msg);
	if (str != NULL)
	{
		while (str[i_count] != NULL)
		{
			//printf("NOW I AM WIRING |%s|\n", str[i_count]);
			write(pipefd[1], str[i_count], strlen(str[i_count]));
			write(pipefd[1], "\n", 1);
			// if (write(pipefd[1], str[i_count], ft_strlen(str[i_count]) + 1) < 0)
			// 	throw_error_custom((t_error_ms){errno, EPART_EXECUTOR,
			// 		EFUNC_WRITE, "function \"write_pipe\" for \'pipe_setting\'"});
			i_count++;
		}
	}
	use_dup2(pipefd[1], STDOUT_FILENO, error_msg);
	use_close(pipefd[1], error_msg);
}

static void read_pipe(int *pipefd, char **str, char *error_msg)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int		i_count;

	i_count = 0;
	use_close(pipefd[1], error_msg);
	use_dup2(pipefd[0], STDIN_FILENO, error_msg);
	if (str != NULL)
	{
		while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0)
		{
			while (i_count < bytes_read)
			{
				printf("%s", &buffer[i_count]);
				i_count += strlen(&buffer[i_count]) + 1;
			}
		}
	}
	use_close(pipefd[0], error_msg);
}
