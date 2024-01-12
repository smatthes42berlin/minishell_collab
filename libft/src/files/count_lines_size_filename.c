/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lines_size_filename.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:41:53 by smatthes          #+#    #+#             */
/*   Updated: 2023/10/15 19:53:44 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

int	count_lines_size_filename(char *filename, t_file_info *file_info)
{
	int	line_num;
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	line_num = count_lines_size_fd(fd, file_info);
	if (close(fd) == -1)
		return (-1);
	return (line_num);
}
