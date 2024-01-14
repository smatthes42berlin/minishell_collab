/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_funcs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:01:01 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/24 12:59:11 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FUNCS_H
# define MINISHELL_FUNCS_H

/* main */
void	init_main_data(t_main_data *main_data);

/* tokenisation/lexer */

int		tokenise(t_main_data *main_data);
void	skip_ws(char **cur_pos);
char	*is_symbol(char c);
char	*is_squote(char c);
char	*is_dquote(char c);
int		has_closing_quote(char *cli_input, char quote_type);
int		get_token(char **cur_pos, t_main_data *main_data);
int		creat_quoted_token(char **cur_pos, t_token *token, char quote_type);
int		append_token_list(t_main_data *main_data, t_token *token);
int		identify_token(char **cur_pos, t_token *token);
t_token	*create_token(void);
int		count_symbols(char *cur_pos);
int		count_characters(char *cur_pos);
int		symbol_is_valid(char *symbol, int symbol_length);
int		create_symbol_token(char **cur_pos, t_token *token);
int		create_text_token(char **cur_pos, t_token *token);

/* parser */

/* executor */

#endif
