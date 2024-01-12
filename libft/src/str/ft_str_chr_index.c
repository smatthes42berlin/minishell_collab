/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_chr_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:02 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:01:38 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

ssize_t	ft_str_chr_index(const char *s, int c)
{
	char	c_cast;
	size_t	i;

	i = 0;
	c_cast = (unsigned char)c;
	while (s[i] != c_cast && s[i])
		i++;
	if (s[i] == c_cast)
		return (i);
	return (-1);
}
