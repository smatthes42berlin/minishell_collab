/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:01:38 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			s_len;
	char			*map_str;
	unsigned int	i;

	s_len = ft_strlen(s);
	map_str = malloc(sizeof(*map_str) * (s_len + 1));
	if (!map_str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		map_str[i] = f(i, s[i]);
		i++;
	}
	map_str[i] = '\0';
	return (map_str);
}
