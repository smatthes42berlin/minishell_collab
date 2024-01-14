/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:16:56 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/14 11:21:05 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_symbols(char *cur_pos)
{
	int	num;

	num = 0;
	while (is_symbol(cur_pos[num]) && cur_pos[num])
		num++;
	return (num);
}

int	count_characters(char *cur_pos)
{
	int	num;

	num = 0;
	while (!is_symbol(cur_pos[num]) && !ft_isspace(cur_pos[num])
		&& cur_pos[num])
		num++;
	return (num);
}

int	symbol_is_valid(char *symbol, int symbol_length)
{
	if (symbol[0] == '<' && symbol[1] != '<')
	{
		printf("ttt\n");
		return (1);
	}
	if (symbol[0] == '>' && symbol[1] != '>')
	{
		printf("%c\n", symbol[0]);
		printf("%c\n", symbol[1]);
		printf("aaa\n");
		return (1);
	}
	if (symbol_length >= 3)
		return (2);
	return (0);
}
