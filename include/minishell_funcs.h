#ifndef MINISHELL_FUNCS_H
# define MINISHELL_FUNCS_H

/* main */
int					init_main_data(t_main_data *main_data);

/* tokenisation/lexer main*/

int					tokenise(t_main_data *main_data);
void				free_token(void *token);
void				free_main_exit(t_main_data *main_data, int program_state,
						int exit_code);

/* tokenisation/lexer 1 create*/

void				skip_ws(char **cur_pos);
char				*is_operator(char c);
char				*is_squote(char c);
char				*is_dquote(char c);
int					has_closing_quote(char *cli_input, char quote_type);
int					get_token(t_main_data *main_data, char **cur_pos);
int					append_token_list(t_main_data *main_data, t_token *token);
int					identify_token(char **cur_pos, t_token *token);
t_token				*create_token(void);
int					count_operators(char *cur_pos);
int					count_characters(char *cur_pos);
int					identify_operator(char **cur_pos, t_token *token);
int					create_operator_token(char **cur_pos, t_token *token);
int					create_word_token(char **cur_pos, t_token *token);
void				print_token_list(t_list_d *token_list);
void				print_token(t_token *token);
int					create_empty_token(t_main_data *main_data, t_token *token);

/* tokenisation/lexer 2 check syntax and get heredoc */

int					check_syntax_n_heredoc(t_main_data *main_data);
int					token_is_operator(t_token *token);
int					check_syntax(t_list_d *cur_token);
int					token_syntax_error(char *token_val);
int					check_heredoc(t_list_d **cur_token);
int					check_heredoc_delim(t_here_doc_info *hdoc_info);
void				init_hdoc_info(char *delim_raw, t_here_doc_info *hdoc_info);
int					copy_unquoted_chars(t_here_doc_info *hdoc_info, int i);
int					handle_quotes(t_here_doc_info *hdoc_info, int *i);
int					read_heredoc(t_here_doc_info *hdoc_info,
						t_list_d **hdoc_op_token);
int					parent_get_str_child(t_list_d **hdoc_op_token, int fd[2],
						int pid, t_here_doc_info *hdoc_info);
int					child_read_hdoc(t_here_doc_info *hdoc_info, int fd[2]);
int					add_heredoc_str_token(t_list_d **hdoc_op_token, char *res,
						t_here_doc_info *hdoc_info);
int					remove_here_doc_token(t_main_data *main_data);
int					free_heredoc_info_code(t_here_doc_info *hdoc_info,
						int code);

/* environment */

int					init_env_vars(t_main_data *main_data, char *envp[]);
int					env_del_var(t_main_data *main_data, char *val);
int					env_set_var(t_main_data *main_data, char *val);
void				env_print(t_main_data *main_data);
char				*env_get_var(t_main_data *main_data, char *key);

/* expander */

int					expand(t_main_data *main_data);

/* parser */

int					parse(t_main_data *main_data);

/* executor */
void				navigate_tree_forward(t_main_data *data, t_node *node, t_pipefd *pipe_struct);
void				type_exec(t_main_data *data, t_node *node, t_pipefd *pipe_struct);
void				type_redim(t_main_data *data, t_node *node, t_pipefd *pipe_struct);
void				type_pipe(t_main_data *data, t_node *node, t_pipefd *pipe_struct);
void				executor(t_main_data *data);
void				free_ast(t_node *node);

/* builtins */
t_node_exec			*check_buildin(t_node *node);
char				*chose_buildin(t_main_data *data, t_node_exec *node, t_pipefd *pipe_struct);
bool				check_and_choose_buildin(t_main_data *data, t_node *node, t_pipefd *pipe_struct_pipe, t_pipefd *pipe_struct_main);
char				*build_pwd(void);
char 				*build_cd (t_main_data *data, t_node_exec *node, t_pipefd *pipefd);

/* execute lib*/
int					open_handler(const char *path, enum e_open_mode mode);
int					close_handler(int fd);
int					access_handler(const char *path, enum e_access_mode mode);
void				execve_handler(const char *file_path, char **argv,
						char **env);
pid_t				fork_handler(void);
enum e_pid_satus	process_status(pid_t pid, bool block);
void				pipe_handler(int *pipefd);
void				pipe_setting(int *pipefd, bool open, char *str);
void				*malloc_handler(size_t bytes);
/*
void				append_node_pid_list(t_list **head, pid_t pid);
void				print_list_pid_list(t_list *head);
void				free_list_pid_list(t_list *head);
void				wait_for_all_processes(t_list *pid_list);
*/

/* error */
void				error_code_handler(int error_code, const char *msg,
						const char *subj, const char *mode);

/* test enviroment */
// -> test cmd!
t_node_exec			*test_cmd_exec(char *name, char *command, char *flag,
						bool inbuild);
t_node_pipe			*test_cmd_pipe(char *name, enum e_node_type type_left,
						enum e_node_type type_right, void *node_left,
						void *node_right);
t_node_redir		*test_cmd_redir(char *name, char *filename,
						enum e_open_mode mode, enum e_std_fd in_or_out,
						enum e_node_type child_typ, void *child_node);
// -> examples
t_node				*set_cmd_1(void);
t_node				*set_cmd_2(void);
t_node				*set_cmd_2_cp(void);
t_node				*set_cmd_3(void);
t_node				*set_cmd_4(void);
t_node				*set_redir_in_1(void);
t_node				*set_redir_in_1_cmd_2(void);
t_node				*set_redir_in_2_cmd_2(void);
t_node				*set_redir_out_1_append(void);
t_node				*set_redir_out_1(void);

void				print_type(t_node *node);

// --build pwd
t_node				*set_pwd_allone(void);
t_node				*set_pwd_beginn_1(void);
t_node				*set_pwd_begin_2(void);
t_node				*set_pwd_end(void);
t_node				*set_pwd_redir_out(void);

t_node				*set_cd_absolut(void);
t_node				*set_cd_relativ(void);
t_node				*set_cd_relativ_revers(void);

#endif
