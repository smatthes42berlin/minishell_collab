/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:16:56 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/24 12:59:47 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_ws(char **cur_pos)
{
	while (ft_isspace(**cur_pos) && **cur_pos)
		(*cur_pos)++;
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
	return (ft_strchr("\"", c));
}

int	has_closing_quote(char *cli_input, char quote_type)
{
	return (ft_str_chr_index(cli_input, quote_type));
}

