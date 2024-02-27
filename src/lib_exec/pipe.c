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

void	pipe_setting_exit_code(int *pipefd, bool open, int *exit_code, char *error_msg)
{
	
	if (open)
	{
		use_close(pipefd[0], error_msg);
		if (write(pipefd[1], exit_code, sizeof(*exit_code)) < 0)
			throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_WRITE, error_msg});
		use_close(pipefd[1], error_msg);
		printf("I SET exit code for pipehandling %i \n\n" , *exit_code);
	}
	else
	{
		use_close(pipefd[1], error_msg);
		if (read(pipefd[0], exit_code, sizeof(*exit_code)) < 0)
			throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_READ, error_msg});
		use_close(pipefd[0], error_msg);
		printf("I GET exit code for pipehandling %i\n\n" , *exit_code);
	}
	
}



// /**
//  * @brief set the given pipefild for close or open
//  *
//  * @param pipefd arry of [2]
//  * @param open if true the pipe is open
//  * @param str str is for the is_inbuilt's function
//  */
// void	pipe_setting(int *pipefd, bool open, char **str, char *error_msg)
// {
// 	if (open)
// 	{
// 		write_pipe(pipefd, str, error_msg);
// 	}
// 	else
// 	{
// 		read_pipe(pipefd, str, error_msg);
// 	}
// }


// static void	write_pipe(int *pipefd, char **str, char *error_msg)
// {
// 	int	i_count;
// 	int	ret;

// 	i_count = 0;
// 	printf("write Pipe -- pipe setting pipefd[0] |%d| pipefd[1] |%d|\n", pipefd[0], pipefd[1]);
// 	use_close(pipefd[0], error_msg);
// 	use_dup2(pipefd[1], STDOUT_FILENO, error_msg);
// 	if (str != NULL)
// 	{
// 		while (str[i_count] != NULL)
// 		{
// 			printf("WRITR : |%s|\n", str[i_count]);
// 			ret = write(pipefd[1], str[i_count], strlen(str[i_count]));
// 			ret = write(pipefd[1], "\n", 1);
// 			printf ("write |%d|\n", ret);
// 			if (ret < 0)
// 			{
// 				ret = throw_error_custom((t_error_ms){errno, EPART_EXECUTOR,
// 						EFUNC_WRITE, error_msg});
// 				break ;
// 			}
// 		i_count++;
// 		}
// 	}
// }

// static void read_pipe(int *pipefd, char **str, char *error_msg)
// {
// 	char	buffer[BUFFER_SIZE];
// 	ssize_t	bytes_read;
// 	int		i_count;

// 	i_count = 0;
// 	printf("read Pipe -- pipe setting pipefd[0] |%d| pipefd[1] |%d|\n", pipefd[0], pipefd[1]);

// 	use_close(pipefd[1], error_msg);
// 	use_dup2(pipefd[0], STDIN_FILENO, error_msg);
// 	if (str != NULL)
// 	{
// 		while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0)
// 		{
// 			while (i_count < bytes_read)
// 			{
// 				printf("%s", &buffer[i_count]);
// 				i_count += strlen(&buffer[i_count]) + 1;
// 			}
// 		}
// 	}
// //	use_close(pipefd[0], error_msg);
// }
