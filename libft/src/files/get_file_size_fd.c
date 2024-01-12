/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_size_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:41:53 by smatthes          #+#    #+#             */
/*   Updated: 2023/10/29 13:10:14 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
