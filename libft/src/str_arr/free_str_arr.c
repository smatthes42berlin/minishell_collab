/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 09:29:22 by smatthes          #+#    #+#             */
/*   Updated: 2023/10/05 11:48:16 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

void	free_str_arr(char **str_arr, int num)
{
	num--;
	while (num >= 0)
	{
		free(str_arr[num]);
		num--;
	}
	free(str_arr);
}
