/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dc_lst_print_whole.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/19 15:27:25 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

static void	print_short(t_list_dc *lst_ptr, const char *type);
static void	print_long(t_list_dc *lst_ptr, const char *type);

void	dc_lst_print_whole(t_list_dc *lst_ptr, const char *longShort,
		const char *type)
{
	if (!lst_ptr)
	{
		ft_printf(CYAN);
		ft_printf("---PASSED EMPTY LIST - NOTHING TO PRINT---\n");
		ft_printf(WHITE);
		return ;
	}
	if (str_are_equal(longShort, "long"))
		print_long(lst_ptr, type);
	if (str_are_equal(longShort, "short"))
		print_short(lst_ptr, type);
	ft_printf(CYAN);
	ft_printf("---ALL PRINTED---\n");
	ft_printf(WHITE);
	return ;
}

static void	print_short(t_list_dc *lst_ptr, const char *type)
{
	if (str_are_equal(type, "int"))
		dc_lst_iter_node(lst_ptr, &dc_lst_print_one_int_short);
	if (str_are_equal(type, "str"))
		dc_lst_iter_node(lst_ptr, &dc_lst_print_one_str_short);
}

static void	print_long(t_list_dc *lst_ptr, const char *type)
{
	if (str_are_equal(type, "int"))
		dc_lst_iter_node(lst_ptr, &dc_lst_print_one_int_long);
	if (str_are_equal(type, "str"))
		dc_lst_iter_node(lst_ptr, &dc_lst_print_one_str_long);
}
