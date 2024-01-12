/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:02 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:01:38 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_u;
	size_t			i;

	i = 0;
	s_u = (unsigned char *)s;
	while (i < n)
	{
		s_u[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
