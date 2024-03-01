#include "minishell.h"

static int	read_line_pipe(t_main_data *data, ssize_t bytes_read, char *buffer);

int	read_pipe(t_main_data *data, t_pipefd *pipe_struct)
{
	ssize_t	bytes_read;
	int		start;
	int		i_count;
	char	buffer[BUFFER_SIZE + 1];

	start = 0;
	i_count = 0;
	use_close(pipe_struct->pipefd[1], "fuction \"read pipe\" for executor");
	bytes_read = read(pipe_struct->pipefd[0], buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (read_line_pipe(data, bytes_read, buffer) < 0)
			return (-1);
		bytes_read = read(pipe_struct->pipefd[0], buffer, BUFFER_SIZE);
	}
	if (start < bytes_read)
	{
		if (env_add_clr(data, &buffer[start]) == -1)
			return (-1); 
	}
	use_close(pipe_struct->pipefd[0], "fuction \"read pipe\" for executor");
	return (0);
}

static int	read_line_pipe(t_main_data *data, ssize_t bytes_read, char *buffer)
{
	int		i_count;
	int		start;

	i_count = 0;
	start = 0;
	while (i_count < bytes_read)
	{
		if (buffer[i_count] == '\n' || buffer[i_count] == '\0')
		{
			buffer[i_count] = '\0';
			if (env_add_clr(data, &buffer[start]) == -1)
				return (-1); 
			start = i_count + 1;
		}
		i_count++;
	}
	if (start < bytes_read)
		ft_memmove(buffer, &buffer[start], bytes_read - start);
	return (0);
}
