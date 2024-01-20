#include "lib_main.h"

int	count_cols_per_line_filename(char *filename, t_file_info *file_info)
{
	int	res;
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	file_info->rows = count_lines_fd(fd);
	if (file_info->rows <= 0)
	{
		file_info->cols = NULL;
		close(fd);
		return (-1);
	}
	if (close(fd) == -1)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	res = count_cols_per_line_fd(fd, file_info);
	if (close(fd) == -1)
		return (-1);
	return (res);
}
