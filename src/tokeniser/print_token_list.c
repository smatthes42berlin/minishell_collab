/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:12:59 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/19 15:33:50 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list(t_list_dc *token_list)
{
	t_list_dc	*head;
	t_list_dc	*next;

	head = token_list;
	if (!token_list)
		return ;
	printf("********TOKEN_LIST\n\n");
	print_token(head->content);
	next = head->next;
	while (next != head)
	{
		print_token(next->content);
		next = next->next;
	}
	return ;
}

void	print_token(t_token *token)
{
	printf("********\n");
	printf("token type = %d\n", token->type);
	printf("token value = %s\n", token->value);
	printf("********\n\n");
}

