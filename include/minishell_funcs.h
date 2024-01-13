/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_funcs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:01:01 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/13 16:53:16 by smatthes         ###   ########.fr       */
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

/* parser */

/* executor */

#endif
