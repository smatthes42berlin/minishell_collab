/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:09:12 by rene              #+#    #+#             */
/*   Updated: 2024/01/16 17:21:57 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*open_mode_to_str(enum e_open_mode mode);

int open_handler(const char *path, enum e_open_mode  mode)
{
    int result;
    
    result = -1;
    if(access_handler(path,FILE_EXISTS) != 0)
        result = open(path, mode | O_CREAT, S_IRWXU);
    else
        result = open(path, mode);
    error_code_handler(errno, "ERR-open path ", path ,open_mode_to_str(mode));   
    return (result);
}

int close_handler(int fd)
{
	int result;
    
    result = -1;
	result = close(fd);
	error_code_handler(errno, "ERR-close (fd)", ft_itoa(fd)," ");
	return (result);
}

/**
 * @brief return the given enum t_access_mode to a String
 * 
 * @param mode mode for [FILE_EXISTS]; [FILE_READABLE]; [FILE_WRITABLE]; [FILE_EXECUTABLE]
 * @return const char* "FILE_EXISTS"; "FILE_READABLE"; "FILE_WRITABLE"; "FILE_EXECUTABLE"
 */
static const char	*open_mode_to_str(enum e_open_mode  mode)
{
	if (mode == FILE_ONLY_READING)
		return ("MODE-FILE_ONLY_READING");
	else if (mode == FILE_ONLY_WRITE)
		return ("MODE-FILE_ONLY_WRITE");
	else if (mode == FILE_ONLY_WRITE_APPEND)
		return ("MODE-FILE_ONLY_WRITE_APPEND");
	else if (mode == FILE_READ_WRITE)
		return ("MODE-FILE_READ_WRITE");
    else if (mode == FILE_READ_WRITE_APPEND)
		return ("MODE-FILE_READ_WRITE_APPEND");
	else
		return ("MODE-UNKNOWN_MODE");
}