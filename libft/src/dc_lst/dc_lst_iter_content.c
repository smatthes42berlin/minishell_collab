/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dc_lst_iter_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/19 17:17:32 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

void	dc_lst_iter_content(t_list_d *lst, void (*f)(void *))
{
	t_list_d	*head;
	t_list_d	*current;

	if (!lst)
		return ;
	head = lst;
	f(head->content);
	current = lst->next;
	while (head != current)
	{
		f(current->content);
		current = current->next;
	}
}
