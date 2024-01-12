/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_cpy_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:31:05 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/11 14:15:51 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib_main.h"

char	**ft_arr_cpy_char(char **arr, int num)
{
	int		i;
	char	**cpy;

	i = 0;
	cpy = malloc(sizeof(*cpy) * (num + 1));
	if (!cpy)
		return (NULL);
	while (i < num)
	{
		cpy[i] = ft_strdup(arr[i]);
		if (!cpy[i])
		{
			free_str_arr(cpy, i - 1);
			return (NULL);
		}
		i++;
	}
	cpy[num] = NULL;
	return (cpy);
}
