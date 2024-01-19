/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dc_lst_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/19 18:33:41 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

static t_list_d	*clear_ret_null(t_list_d **new_head, void (*del)(void *));

t_list_d	*dc_lst_map(t_list_d *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list_d	*old_head;
	t_list_d	*cur_old;
	t_list_d	*new_head;
	t_list_d	*new_node;

	new_head = NULL;
	old_head = lst;
	if (lst == NULL)
		return (new_head);
	new_head = dc_lst_new(f(lst->content));
	if (!new_head)
		return (NULL);
	cur_old = lst->next;
	while (old_head != cur_old)
	{
		new_node = dc_lst_new(f(cur_old->content));
		if (!new_node)
			return (clear_ret_null(&new_head, del));
		dc_lst_add_back(&new_head, new_node);
		cur_old = cur_old->next;
	}
	return (new_head);
}

static t_list_d	*clear_ret_null(t_list_d **new_head, void (*del)(void *))
{
	dc_lst_clear(new_head, del);
	return (NULL);
}
