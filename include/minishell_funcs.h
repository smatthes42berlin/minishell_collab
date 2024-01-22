/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_funcs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:01:01 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/22 08:44:01 by rene             ###   ########.fr       */
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
void navigate_tree_forward(t_node *node, t_list **pid_list);



/* execute lib*/
int     open_handler(const char *path, enum e_open_mode  mode);
int     close_handler(int fd);
int		access_handler(const char *path, enum e_access_mode mode);
void	execve_handler(t_node_exec *exec);
pid_t   fork_handler(void);
t_pid_list *init_pid_list();
enum    e_pid_satus process_status(pid_t pid, bool block);
void    pipe_handler(int *pipefd);
void    pipe_setting(int *pipefd, bool open);
void 	*malloc_handler(size_t bytes);
t_list *create_node(pid_t pid);
void append_node(t_list **head, pid_t pid);
void print_list(t_list *head);
void free_list(t_list *head);
t_list *clone_list(t_list *original);


/* error */
void error_code_handler(int error_code, const char *msg, const char *subj, const char *mode);


/* test enviroment */
t_node_exec *test_cmd_exec(char *name, char *command, char *flag);
t_node_pipe *test_cmd_pipe(char *name, enum e_node_type type_left, enum e_node_type type_right, void *node_left, void *node_right);
t_node_redir *test_cmd_redir(char *name, char *filename, enum e_open_mode mode, enum e_std_fd in_or_out,
                            enum e_node_type child_typ, void *child_node);

void	test_read(void);
void list_test_use(void);
#endif
