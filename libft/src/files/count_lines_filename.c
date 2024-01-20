#include "lib_main.h"

int	count_lines_filename(char *filename)
{
	int	line_num;
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	line_num = count_lines_fd(fd);
	if (close(fd) == -1)
		return (-1);
	return (line_num);
}
