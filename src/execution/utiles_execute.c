#include "minishell.h"

int write_str_arr_pipe(int *pipefd, char **str, char *err_msg) {
    int i_count;
    int ret;
	size_t len;

    i_count = 0;
    while (str[i_count] != NULL) 
	{
        len = strlen(str[i_count]);
		//printf("WRITE PUFFER %s\n", str[i_count]);
        ret = write(pipefd[1], str[i_count], len +  1 );
        if (ret < 0) {
            ret = throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_WRITE, err_msg});
            break;
        }
        i_count++;
    }
    return ret;
}

int read_str_arr_pipe(int *pipefd)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int		i_count;
	int		ret;

	i_count = 0;
	ret = 0;
	while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0)
	{
		while (i_count < bytes_read)
		{
			printf("%s", &buffer[i_count]);
			i_count += strlen(&buffer[i_count]) + 1;
		}
		if (bytes_read < 0)
		{
			ret = throw_error_custom((t_error_ms){errno, EPART_EXECUTOR,
					EFUNC_READ, "function \"left_side\" read **str to pipe"});
			break ;
		}
	}
	return (ret);
}

int write_pipe_to_executor_pipe(int *pipefd, char **str_arr, char *err_msg)
{
	int ret;

	ret = use_close(pipefd[0], err_msg);
	ret = write_str_arr_pipe(pipefd, str_arr, err_msg);
	ret = use_close(pipefd[1], err_msg);
	return (ret);
}