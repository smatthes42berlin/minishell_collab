/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:39:42 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:02:57 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

size_t	handle_c(int fd, va_list args)
{
	unsigned char	c;

	c = (unsigned char)va_arg(args, int);
	return (ft_putchar_fd_len(c, fd));
}
