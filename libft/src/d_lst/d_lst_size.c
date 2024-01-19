/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_lst_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/19 18:11:38 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

int	d_lst_size(t_list_d *lst)
{
	int			size;

	size = 0;
	if (lst == NULL)
		return (size);
	size++;
	while (lst->next)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
