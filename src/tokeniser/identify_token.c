/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:16:56 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/14 11:22:59 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	identify_token(char **cur_pos, t_token *token)
{
	if (ft_strchr("\"", **cur_pos))
		return (creat_quoted_token(cur_pos, token, '"'));
	else if (ft_strchr("'", **cur_pos))
		return (creat_quoted_token(cur_pos, token, '\''));
	else if (is_symbol(**cur_pos))
		return (create_symbol_token(cur_pos, token));
	else
		return (create_text_token(cur_pos, token));
	return (1);
}

int	create_text_token(char **cur_pos, t_token *token)
{
	char	*token_val;
	int		num_characters;

	num_characters = count_characters(*cur_pos);
	if (ft_str_n_dup_int(*cur_pos, num_characters + 1, &token_val) == -1)
		return (printf("Error: duplicating string for token\n"));
	token->type = TEXT;
	token->value = token_val;
	*cur_pos = *cur_pos + num_characters;
	printf("created text token\n");
	return (0);
}

int	create_symbol_token(char **cur_pos, t_token *token)
{
	char	*token_val;
	int		num_symbols;
	int		symbol_valid;

	num_symbols = count_symbols(*cur_pos);
	if (ft_str_n_dup_int(*cur_pos, num_symbols + 1, &token_val) == -1)
		return (printf("Error: duplicating string for token\n"));
	token->type = SYMBOL;
	token->value = token_val;
	symbol_valid = symbol_is_valid(token_val, num_symbols);
	printf("symbol length %d\n", num_symbols);
	if (symbol_valid)
		return (printf("Syntax error near unexpected Token %c\n",
						(*cur_pos)[symbol_valid]));
	*cur_pos = *cur_pos + num_symbols;
	printf("created symbol token\n");
	return (0);
}

int	creat_quoted_token(char **cur_pos, t_token *token, char quote_type)
{
	int		closing_quote;
	char	*token_val;

	(*cur_pos)++;
	closing_quote = has_closing_quote(*cur_pos, quote_type);
	if (closing_quote == -1)
		return (printf("Error: no closing quote\n"));
	if (ft_str_n_dup_int(*cur_pos, closing_quote, &token_val) == -1)
		return (printf("Error: duplicating string for token\n"));
	if (quote_type == '"')
		token->type = DQTEXT;
	else
		token->type = SQTEXT;
	token->value = token_val;
	*cur_pos = *cur_pos + closing_quote + 1;
	printf("created quoted token\n");
	return (0);
}
