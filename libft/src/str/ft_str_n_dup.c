/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_n_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:01:38 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

char	*ft_str_n_dup(const char *s, int n)
{
	size_t	str_len;
	char	*new_str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (n == 0)
	{
		str_len = ft_strlen(s);
		n = str_len + 1;
	}
	new_str = malloc((n) * sizeof(*new_str));
	if (!new_str)
		return (NULL);
	while (s[i] && i < n - 1)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
