/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:01:38 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

static size_t	get_num_digs(long n_l);

char	*ft_itoa(int n)
{
	long	n_l;
	size_t	length;
	char	*res;

	n_l = (long)n;
	length = get_num_digs(n_l);
	if (n < 0 && length++)
		n_l *= -1;
	res = malloc((sizeof(*res) * (length + 1)));
	if (!res)
		return (NULL);
	if (n < 0)
		*res = '-';
	res[length--] = '\0';
	while (n_l >= 10)
	{
		res[length--] = (n_l % 10) + '0';
		n_l = n_l / 10;
	}
	res[length] = (n_l % 10) + '0';
	return (res);
}

static size_t	get_num_digs(long n_l)
{
	size_t	length;
	long	res;

	length = 1;
	res = n_l;
	if (n_l < 0)
		res *= -1;
	while (res >= 10)
	{
		length++;
		res = res / 10;
	}
	return (length);
}
