/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:02 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:01:38 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

char	*ft_strchr(const char *s, int c)
{
	char	c_cast;

	c_cast = (unsigned char)c;
	if (*s == c_cast)
		return ((char *)s);
	while (*s != c_cast && *s)
		s++;
	if (*s == c_cast)
		return ((char *)s);
	return (NULL);
}
