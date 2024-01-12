/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:39:42 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:03:12 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

size_t	handle_u(int fd, va_list args)
{
	char			*base;
	unsigned long	nbr;

	nbr = (unsigned long)va_arg(args, unsigned int);
	base = "0123456789";
	return (ft_putnbr_base_fd_ul(fd, nbr, base));
}
