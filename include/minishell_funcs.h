#ifndef MINISHELL_FUNCS_H
# define MINISHELL_FUNCS_H

/* main */
void				init_main_data(t_main_data *main_data);

/* tokenisation/lexer */

int					tokenise(t_main_data *main_data);
void				skip_ws(char **cur_pos);
char				*is_symbol(char c);
char				*is_squote(char c);
char				*is_dquote(char c);

/* parser */

/* executor */
void				navigate_tree_forward(t_node *node);
void				type_exec(t_node *node);
void				type_redim(t_node *node);
void				type_pipe(t_node *node);
void				executor(void);

/* execute lib*/
int					open_handler(const char *path, enum e_open_mode mode);
int					close_handler(int fd);
int					access_handler(const char *path, enum e_access_mode mode);
void				execve_handler(const char *file_path, char **argv,
						char **env);
pid_t				fork_handler(void);
enum e_pid_satus	process_status(pid_t pid, bool block);
void				pipe_handler(int *pipefd);
void				pipe_setting(int *pipefd, bool open);
void				*malloc_handler(size_t bytes);
void				append_node_pid_list(t_list **head, pid_t pid);
void				print_list_pid_list(t_list *head);
void				free_list_pid_list(t_list *head);
void				wait_for_all_processes(t_list *pid_list);

/* error */
void				error_code_handler(int error_code, const char *msg,
						const char *subj, const char *mode);

/* test enviroment */
// -> test cmd!
t_node_exec			*test_cmd_exec(char *name, char *command, char *flag);
t_node_pipe			*test_cmd_pipe(char *name, enum e_node_type type_left,
						enum e_node_type type_right, void *node_left,
						void *node_right);
t_node_redir		*test_cmd_redir(char *name, char *filename,
						enum e_open_mode mode, enum e_std_fd in_or_out,
						enum e_node_type child_typ, void *child_node);
// -> examples
t_node				*set_cmd_1(void);
t_node				*set_cmd_2(void);
t_node				*set_cmd_3(void);
t_node				*set_cmd_4(void);
t_node				*set_redir_in_1(void);
t_node				*set_redir_in_1_cmd_2(void);
t_node				*set_redir_out_1(void);
void				print_type(t_node *node);

#endif
