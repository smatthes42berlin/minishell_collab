/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 07:24:51 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/11 15:58:46 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		chars_printed;

	va_start(args, format);
	chars_printed = ft_vdprintf(1, format, args);
	va_end(args);
	return (chars_printed);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		chars_printed;

	va_start(args, format);
	chars_printed = ft_vdprintf(fd, format, args);
	va_end(args);
	return (chars_printed);
}
