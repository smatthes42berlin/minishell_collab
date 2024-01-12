/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dc_lst_pop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/19 09:49:41 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

t_list_dc	*dc_lst_pop(t_list_dc **lst)
{
	t_list_dc	*old_head;

	if (!lst || !*lst)
		return (NULL);
	old_head = *lst;
	if (dc_lst_exactly_one(*lst))
		*lst = NULL;
	else
	{
		*lst = old_head->next;
		old_head->next->prev = old_head->prev;
		old_head->prev->next = old_head->next;
		old_head->next = old_head;
		old_head->prev = old_head;
	}
	return (old_head);
}
