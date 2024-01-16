/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_funcs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:01:01 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/16 17:31:32 by rkost            ###   ########.fr       */
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
void	init_main_data_test(t_main_data *main_data);
void	test_exece(void);
void	test_read(void);


/* execute lib*/
int     open_handler(const char *path, enum e_open_mode  mode);
int     close_handler(int fd);
int		access_handler(const char *path, enum e_access_mode mode);
void	execve_handler(t_node_exec *exec);

/* error */
void error_code_handler(int error_code, const char *msg, const char *subj, const char *mode);

#endif
