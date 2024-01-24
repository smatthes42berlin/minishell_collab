#include "lib_main.h"

int	get_file_size_filename(char *filename)
{
	int	line_num;
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	line_num = get_file_size_fd(fd);
	if (close(fd) == -1)
		return (-1);
	return (line_num);
}
