/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dc_lst_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/18 12:29:19 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

t_list_dc	*dc_lst_map(t_list_dc *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list_dc	*old_head;
	t_list_dc	*cur_old;
	t_list_dc	*new_head;
	t_list_dc	*new_node;

	new_head = NULL;
	old_head = lst;
	if (lst == NULL)
		return (new_head);
	new_head = dc_lst_new(f(lst->content));
	cur_old = lst->next;
	new_node = new_head;
	while (old_head != cur_old)
	{
		new_node = dc_lst_new(f(cur_old->content));
		if (!new_node)
		{
			dc_lst_clear(&new_head, del);
			return (NULL);
		}
		dc_lst_add_back(&new_head, new_node);
		cur_old = cur_old->next;
	}
	return (new_head);
}
