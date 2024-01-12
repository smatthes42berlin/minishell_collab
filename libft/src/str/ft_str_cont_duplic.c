/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_cont_duplic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:53:05 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:01:38 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

int	ft_str_cont_duplic(const char *str)
{
	int				count[256];
	int				i;
	int				num_cur_char;
	unsigned char	cur_char;

	ft_arr_set_int(count, 256, 0);
	i = 0;
	while (str[i])
	{
		cur_char = (unsigned char)str[i];
		num_cur_char = count[cur_char] + 1;
		count[cur_char] = num_cur_char;
		if (num_cur_char > 1)
			return (1);
		i++;
	}
	return (0);
}
