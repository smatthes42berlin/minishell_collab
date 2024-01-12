/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:02 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:01:38 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_u;
	unsigned char	c_u;
	size_t			i;

	i = 0;
	s_u = (unsigned char *)s;
	c_u = (unsigned char)c;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (s_u[i] == c_u)
			return ((void *)(s_u + i));
		i++;
	}
	return (NULL);
}
