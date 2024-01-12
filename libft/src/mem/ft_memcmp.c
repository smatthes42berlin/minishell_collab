/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:02 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:01:38 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_u;
	unsigned char	*s2_u;
	size_t			i;

	if (n == 0)
		return (0);
	i = 0;
	s1_u = (unsigned char *)s1;
	s2_u = (unsigned char *)s2;
	while (s1_u[i] == s2_u[i] && i < (n - 1))
		i++;
	return (s1_u[i] - s2_u[i]);
}
