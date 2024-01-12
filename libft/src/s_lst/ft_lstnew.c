/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:01:38 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst_ptr;

	lst_ptr = malloc(sizeof(*lst_ptr));
	if (!lst_ptr)
	{
		return (NULL);
	}
	lst_ptr->next = NULL;
	lst_ptr->content = content;
	return (lst_ptr);
}
