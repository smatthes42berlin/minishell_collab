#include "lib_main.h"

int	get_file_size_fd(int fd)
{
	int		num_bytes;
	int		file_size;
	char	buffer[BUFFER_SIZE];

	num_bytes = read(fd, buffer, BUFFER_SIZE);
	if (num_bytes == 0)
		return (0);
	file_size = num_bytes;
	while (num_bytes != 0)
	{
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if (num_bytes == -1)
			return (-1);
		file_size += num_bytes;
	}
	return (file_size);
}
