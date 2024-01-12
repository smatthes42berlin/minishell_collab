/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_arr_int_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:31:05 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/11 15:54:45 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib_main.h"

int	int_arr_int_index(int *arr, int search, int arr_len)
{
	int	i;

	i = 0;
	while (i < arr_len)
	{
		if (arr[i] == search)
			return (i);
		i++;
	}
	return (-1);
}
