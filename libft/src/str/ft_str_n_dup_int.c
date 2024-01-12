/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_n_dup_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2023/11/10 14:34:59 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

int	ft_str_n_dup_int(const char *s, int n, char **res)
{
	size_t	str_len;
	int		i;

	i = 0;
	*res = NULL;
	if (!s)
		return (1);
	if (n == 0)
	{
		str_len = ft_strlen(s);
		n = str_len + 1;
	}
	*res = malloc((n) * sizeof(**res));
	if (!(*res))
		return (-1);
	while (s[i] && i < n - 1)
	{
		(*res)[i] = s[i];
		i++;
	}
	(*res)[i] = '\0';
	return (1);
}
