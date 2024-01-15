/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:53:53 by rkost             #+#    #+#             */
/*   Updated: 2024/01/15 17:42:40 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			access_error_handler_1(int error_code, t_access_mode mode);
static void			access_error_handler_2(int error_code, t_access_mode mode);

/**
 * @brief using for checking the right of the given path
 * 
 * @param path 
 * @param mode checking mode for [FILE_EXISTS]; [FILE_READABLE]; [FILE_WRITABLE]; [FILE_EXECUTABLE]
 * @return int 	[0] 	- File was exapted with this mode;
 * 				[-1]	- error return;
 */

int	safe_access_handler(char *path, t_access_mode mode)
{
	int	result;

	result = -1;
	if (FILE_EXISTS == mode || FILE_READABLE == mode || FILE_WRITABLE == mode
		|| FILE_EXECUTABLE == mode)
		result = access(path, mode);
	else
	{
		printf("ERROR ACCESS - Wrong Mode given");
		return (result);
	}
	access_error_handler_1(result, mode);
	return (result);
}

/**
 * @brief return the given enum t_access_mode to a String
 * 
 * @param mode mode for [FILE_EXISTS]; [FILE_READABLE]; [FILE_WRITABLE]; [FILE_EXECUTABLE]
 * @return const char* "FILE_EXISTS"; "FILE_READABLE"; "FILE_WRITABLE"; "FILE_EXECUTABLE"
 */
static const char	*access_mode_to_str(t_access_mode mode)
{
	if (mode == FILE_EXISTS)
		return ("FILE_EXISTS");
	else if (mode == FILE_READABLE)
		return ("FILE_READABLE");
	else if (mode == FILE_WRITABLE)
		return ("FILE_WRITABLE");
	else if (mode == FILE_EXECUTABLE)
		return ("FILE_EXECUTABLE");
	else
		return ("UNKNOWN_MODE");
}
/**
 * @brief Errorhandling for 'access' function.
 * Because norminette accept max. 25 lines. 
 * -> split in 2 function 
 * 
 * @param error_code 
 * @param mode 
 */

static void	access_error_handler_1(int error_code, t_access_mode mode)
{
	if (0 == error_code)
		return ;
	else if (EACCES == error_code)
		printf("EACCES ERR-access MODE-%s: %s\n", access_mode_to_str(mode),
			strerror(error_code));
	else if (EBADF == error_code)
		printf("EBADF ERR-access MODE-%s: %s\n", access_mode_to_str(mode),
			strerror(error_code));
	else if (EFAULT == error_code)
		printf("EFAULT ERR-access MODE-%s: %s\n", access_mode_to_str(mode),
			strerror(error_code));
	else if (EINVAL == error_code)
		printf("EINVAL ERR-access MODE-%s: %s\n", access_mode_to_str(mode),
			strerror(error_code));
	else if (EIO == error_code)
		printf("EIO ERR-access MODE-%s: %s\n", access_mode_to_str(mode),
			strerror(error_code));
	else if (ELOOP == error_code)
		printf("ELOOP ERR-access MODE-%s: %s\n", access_mode_to_str(mode),
			strerror(error_code));
	else if (ENAMETOOLONG == error_code)
		printf("ENAMETOOLONG ERR-access MODE-%s: %s\n",
			access_mode_to_str(mode), strerror(error_code));
	else
		access_error_handler_2(error_code, mode);
}
/**
 * @brief 'access_error_handler' -> split in 2 function.
 * Because norminette accept max. 25 lines.
 * 
 * @param error_code 
 * @param mode 
 */

static void	access_error_handler_2(int error_code, t_access_mode mode)
{
	if (ENOENT == error_code)
		printf("ENOENT ERR-access MODE-%s: %s\n", access_mode_to_str(mode),
			strerror(error_code));
	else if (ENOMEM == error_code)
		printf("ENOMEM ERR-access MODE-%s: %s\n", access_mode_to_str(mode),
			strerror(error_code));
	else if (ENOTDIR == error_code)
		printf("ENOTDIR ERR-access MODE-%s: %s\n", access_mode_to_str(mode),
			strerror(error_code));
	else if (EPERM == error_code)
		printf("EPERM ERR-access MODE-%s: %s\n", access_mode_to_str(mode),
			strerror(error_code));
	else if (EROFS == error_code)
		printf("EROFS ERR-access MODE-%s: %s\n", access_mode_to_str(mode),
			strerror(error_code));
	else if (ETXTBSY == error_code)
		printf("ETXTBSY ERR-access MODE-%s: %s\n", access_mode_to_str(mode),
			strerror(error_code));
}