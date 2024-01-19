/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:16:56 by smatthes          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/20 09:29:20 by smatthes         ###   ########.fr       */
=======
/*   Updated: 2024/01/19 15:20:56 by smatthes         ###   ########.fr       */
>>>>>>> 9d8782a (creation of token list workin 1.0)
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
	if (is_symbol(*symbol) && symbol_length == 1)
		return (0);
	if (symbol[0] == '<' && symbol[1] != '<')
		return (1);
	if (symbol[0] == '>' && symbol[1] != '>')
		return (1);
	if (symbol_length >= 3)
		return (2);
	return (0);
}
