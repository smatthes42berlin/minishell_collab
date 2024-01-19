/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_funcs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:01:01 by smatthes          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/20 09:30:18 by smatthes         ###   ########.fr       */
=======
/*   Updated: 2024/01/19 15:31:27 by smatthes         ###   ########.fr       */
>>>>>>> 9d8782a (creation of token list workin 1.0)
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
void	print_token_list(t_list_dc *token_list);
void	print_token(t_token *token);
int		create_empty_token(char **cur_pos, t_token *token);

/* parser */

/* executor */

#endif
