/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_lst_exactly_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/19 18:06:14 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

int	d_lst_exactly_two(t_list_d *lst_ptr)
{
	if (!lst_ptr)
		return (0);
	if (!lst_ptr->next)
		return (0);
	if (!lst_ptr->next->next)
		return (1);
	return (0);
}
