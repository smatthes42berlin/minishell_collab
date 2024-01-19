/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_lst_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/19 17:23:28 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

void	d_lst_add_back(t_list_d **lst, t_list_d *new)
{
	t_list_d	*last;

	if (!new)
		return ;
	last = d_lst_last(*lst);
	if (!last)
		*lst = new;
	new->prev = last;
	new->next = NULL;
	last->next = new;
}
