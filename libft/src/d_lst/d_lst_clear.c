/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_lst_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/19 18:09:24 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

void	d_lst_clear(t_list_d **lst, void (*del)(void *))
{
	t_list_d	*temp;
	t_list_d	*current;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current->next)
	{
		temp = current;
		current = current->next;
		d_lst_del_one(temp, del);
	}
	d_lst_del_one(current, del);
	*lst = NULL;
}
