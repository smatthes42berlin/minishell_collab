/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_funcs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:01:01 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/20 19:21:17 by rene             ###   ########.fr       */
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
void 	navigate_tree_forward(t_node *node);



/* execute lib*/
int     open_handler(const char *path, enum e_open_mode  mode);
int     close_handler(int fd);
int		access_handler(const char *path, enum e_access_mode mode);
void	execve_handler(t_node_exec *exec);
pid_t   fork_handler(void);
enum    e_pid_satus process_status(pid_t pid, bool block);
void    pipe_handler(int *pipefd);
void    pipe_setting(int *pipefd, bool open);
void 	*malloc_handler(size_t bytes);

/* error */
void error_code_handler(int error_code, const char *msg, const char *subj, const char *mode);


/* test */
t_node_exec *test_cmd_exec(char *command, char *commandname, char *flag);
t_node_pipe *test_cmd_pipe(char *name, enum e_node_type type_left, enum e_node_type type_right, void *node_left, void *node_right);





void	test_exece(void);
void	test_read(void);
void	init_main_data_test(t_main_data *main_data);
void list_test_use(void);
#endif
