/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dc_lst_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/19 17:17:33 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

void	dc_lst_clear(t_list_d **lst, void (*del)(void *))
{
	t_list_d	*temp;
	t_list_d	*current;
	t_list_d	*head;

	if (!lst || !*lst)
		return ;
	head = *lst;
	current = (*lst)->next;
	while (head != current)
	{
		temp = current;
		current = current->next;
		dc_lst_del_one(temp, del);
	}
	dc_lst_del_one(head, del);
	*lst = NULL;
}
