#include "lib_main.h"

static void	parse_buffer(char *buffer, int num_bytes, t_file_info *file_info);
static void	handle_newline(t_file_info *file_info, int *cur_row, int *state,
				int *num_col_cur_row);
static void	reset_static(int *state, int *cur_row, int *num_col_cur_row);

// have to use function count_cols_per_line_filename
// because first you have to read whole file to get num of lines

int	count_cols_per_line_fd(int fd, t_file_info *file_info)
{
	char	buffer[BUFFER_SIZE];
	int		num_bytes;

	file_info->cols = malloc(sizeof(file_info->cols) * file_info->rows);
	if (!file_info->cols)
		return (-1);
	num_bytes = read(fd, buffer, BUFFER_SIZE);
	while (num_bytes != 0)
	{
		if (num_bytes == -1)
			return (-1);
		parse_buffer(buffer, num_bytes, file_info);
		num_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	return (1);
}

static void	parse_buffer(char *buffer, int num_bytes, t_file_info *file_info)
{
	int			i;
	static int	state = 0;
	static int	cur_row = 0;
	static int	num_col_cur_row = 0;

	i = 0;
	while (i < num_bytes)
	{
		if (buffer[i] == '\n')
			handle_newline(file_info, &cur_row, &state, &num_col_cur_row);
		else if (state == 0 && buffer[i] != file_info->sep)
		{
			state = 1;
			num_col_cur_row++;
		}
		else if (state == 1 && buffer[i] == file_info->sep)
			state = 0;
		i++;
	}
	if (num_bytes < BUFFER_SIZE)
	{
		file_info->cols[cur_row] = num_col_cur_row;
		reset_static(&state, &cur_row, &num_col_cur_row);
	}
}

static void	handle_newline(t_file_info *file_info, int *cur_row, int *state,
		int *num_col_cur_row)
{
	file_info->cols[*cur_row] = *num_col_cur_row;
	*state = 0;
	*num_col_cur_row = 0;
	(*cur_row)++;
}

static void	reset_static(int *state, int *cur_row, int *num_col_cur_row)
{
	*state = 0;
	*cur_row = 0;
	*num_col_cur_row = 0;
}
