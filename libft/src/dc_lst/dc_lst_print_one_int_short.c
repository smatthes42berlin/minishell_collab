/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dc_lst_print_one_int_short.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/19 17:17:32 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

void	dc_lst_print_one_int_short(void *lst_ptr_void)
{
	t_list_d	*lst_ptr;

	if (!lst_ptr_void)
		return ;
	lst_ptr = (t_list_d *)lst_ptr_void;
	ft_printf("%d\n", *((int *)lst_ptr->content));
	dc_lst_print_sep();
	return ;
}
