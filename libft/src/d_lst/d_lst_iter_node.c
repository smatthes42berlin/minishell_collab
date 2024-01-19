/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_lst_iter_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/19 19:05:29 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

void	d_lst_iter_node(t_list_d *lst, void (*f)(void *))
{
	t_list_d	*current;

	if (!lst)
		return ;
	f(lst);
	current = lst->next;
	while (current)
	{
		f(current);
		current = current->next;
	}
}
