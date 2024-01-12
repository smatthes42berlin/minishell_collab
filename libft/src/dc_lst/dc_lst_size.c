/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dc_lst_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/12 18:28:31 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

int	dc_lst_size(t_list_dc *lst)
{
	int			size;
	t_list_dc	*head;

	size = 0;
	head = lst;
	if (lst == NULL)
		return (size);
	size++;
	lst = lst->next;
	while (head != lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
