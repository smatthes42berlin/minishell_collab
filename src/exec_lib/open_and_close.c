/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:09:12 by rene              #+#    #+#             */
/*   Updated: 2024/01/16 14:39:09 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*open_mode_to_str(t_en_open_mode mode);

int open_handler(const char *path, t_en_open_mode mode)
{
    int result;
    
    result = -1;
    if(safe_access_handler(&path,FILE_EXISTS) != 0)
        result = open(path, mode | O_CREAT, S_IRWXU);
    else
        result = open(path, mode);
    error_code_handler(errno, "ERR-open", open_mode_to_str(open));   
    return (result);
}

int close_handler(int fd)
{
	int result;
    
    result = -1;
	result = close(fd);
	error_code_handler(errno, "ERR-close", " ");
	return (result);
}

/**
 * @brief return the given enum t_access_mode to a String
 * 
 * @param mode mode for [FILE_EXISTS]; [FILE_READABLE]; [FILE_WRITABLE]; [FILE_EXECUTABLE]
 * @return const char* "FILE_EXISTS"; "FILE_READABLE"; "FILE_WRITABLE"; "FILE_EXECUTABLE"
 */
static const char	*open_mode_to_str(t_en_open_mode mode)
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