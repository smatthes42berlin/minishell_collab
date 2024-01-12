/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cap_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:46:12 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:02:59 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

size_t	handle_cap_x(int fd, va_list args)
{
	char			*base;
	unsigned long	nbr;

	nbr = (unsigned long)va_arg(args, unsigned int);
	base = "0123456789ABCDEF";
	return (ft_putnbr_base_fd_ul(fd, nbr, base));
}
