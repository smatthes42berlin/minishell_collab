/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_lst_add_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/19 17:17:33 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

void	d_lst_add_front(t_list_d **lst, t_list_d *new)
{
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		new->next = *lst;
		new->prev = NULL;
		(*lst)->prev = new;
	}
	*lst = new;
}
