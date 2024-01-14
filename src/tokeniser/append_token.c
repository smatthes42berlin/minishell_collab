/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:12:59 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/14 10:14:26 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_token_list(t_main_data *main_data, t_token *token)
{
	t_list_dc	*new_lst_elem;

	new_lst_elem = dc_lst_new(token);
	if (!new_lst_elem)
		return (printf("Error: creating new list elem for token"));
	dc_lst_add_back(&main_data->token_list, new_lst_elem);
	return (0);
}
