#include "minishell.h"

static const char	*open_mode_to_str(enum e_open_mode mode);

/**
 * @brief Using the funktion for safe open
 *
 * @param path filepath
 * @param mode
 * @return int -- the number of the file descripter
 */
int	open_handler(const char *path, enum e_open_mode mode)
{
	int	result;

	if (mode == FILE_ONLY_READING)
	{
		if (access_handler(path, FILE_EXISTS) == 0)
			result = open(path, mode);
		else
		{
			error_code_handler(errno, "ERR-access", 
				" File don't exist -> Path: ", path);
			return (-1);
		}
	}
	else
		result = open(path, mode | O_CREAT, 0644);
	if (result == -1)
	{
		error_code_handler(errno, "ERR-open path ", path,
			open_mode_to_str(mode));
	}
	return (result);
}

/**
 * @brief use the function for safe close
 *
 * @param fd -- file descripter
 * @return int -- errno nbr
 */
int	close_handler(int fd)
{
	int	result;

	result = -1;
	result = close(fd);
	error_code_handler(errno, "ERR-close (fd)", ft_itoa(fd), " ");
	return (result);
}

/**
 * @brief return the given enum e_open_mode to a String
 *
 * @param mode
 * @return const char*
 */
static const char	*open_mode_to_str(enum e_open_mode mode)
{
	if (mode == FILE_ONLY_READING)
		return ("MODE-FILE_ONLY_READING");
	else if (mode == FILE_ONLY_WRITE)
		return ("MODE-FILE_ONLY_WRITE");
	else if (mode == FILE_ONLY_WRITE_APPEND)
		return ("MODE-FILE_ONLY_WRITE_APPEND");
	else
		return ("MODE-UNKNOWN_MODE");
}