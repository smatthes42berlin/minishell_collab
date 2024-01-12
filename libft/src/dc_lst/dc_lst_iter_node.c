/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dc_lst_iter_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/19 09:51:12 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

void	dc_lst_iter_node(t_list_dc *lst, void (*f)(void *))
{
	t_list_dc	*head;
	t_list_dc	*current;

	if (!lst)
		return ;
	head = lst;
	f(head);
	current = lst->next;
	while (head != current)
	{
		f(current);
		current = current->next;
	}
}
