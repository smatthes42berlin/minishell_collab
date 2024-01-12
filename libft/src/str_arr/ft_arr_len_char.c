/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_len_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:31:05 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:01:38 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib_main.h"

size_t	ft_arr_len_char(char **arr)
{
	size_t	arr_len;

	arr_len = 0;
	if (!arr || !arr[0])
		return (arr_len);
	while (arr[arr_len])
		arr_len++;
	return (arr_len);
}
