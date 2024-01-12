/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_len_only_print.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:01:38 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

int		ft_isprint(int c);
size_t	ft_putchar_fd_len(char c, int fd);

size_t	ft_putstr_fd_len_only_print(char *s, int fd)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (ft_isprint(s[i]))
		{
			ft_putchar_fd_len(s[i], fd);
			j++;
		}
		i++;
	}
	return (j);
}
