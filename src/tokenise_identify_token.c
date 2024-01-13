/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_identify_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:16:56 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/13 14:20:53 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_ws(char **cur_pos)
{
	while (ft_isspace(**cur_pos) && **cur_pos)
	{
		(*cur_pos)++;
	}
}

char	*is_symbol(char c)
{
	return (ft_strchr("<>|", c));
}

char	*is_squote(char c)
{
	return (ft_strchr("'", c));
}

char	*is_dquote(char c)
{
	return (ft_strchr('"', c));
}
