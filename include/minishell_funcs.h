#ifndef MINISHELL_FUNCS_H
# define MINISHELL_FUNCS_H

/* signals */

int			ignore_signals(int signals);
void		handle_ctrl_c_sigint_interactive(int signum);
int			start_signals_interactive(void);
int			end_signals_interactive(void);
int			set_signal(int signal, void (*func)(int));
int			restore_default_signals(int signals);

/* main */

int			reset_main_data(t_main_data *main_data);
t_main_data	*get_main_data(void);
int			check_ctrl_d(t_main_data *main_data);
bool		only_newline_entered(t_main_data *main_data);

/* tokenisation/lexer main*/

int			tokenise(t_main_data *main_data);
void		free_token(void *token);
void		free_main_exit(t_main_data *main_data, int exit_code);

/* gen util */

void		skip_ws(char **cur_pos);
char		*is_operator(char c);
char		*is_squote(char c);
char		*is_dquote(char c);
int			has_closing_quote(char *cli_input, char quote_type);
int			get_token(t_main_data *main_data, char **cur_pos);
int			append_token_list(t_main_data *main_data, t_token *token);
int			identify_token(char **cur_pos, t_token *token);
t_token		*create_token(void);
int			count_operators(char *cur_pos);
int			count_characters(char *cur_pos);
int			identify_operator(char **cur_pos, t_token *token);
int			create_operator_token(char **cur_pos, t_token *token);
int			create_word_token(char **cur_pos, t_token *token);
void		print_token_list(t_list_d *token_list);
void		print_token(t_token *token);
int			create_empty_token(t_main_data *main_data, t_token *token);
bool		token_is_operator_token(t_token *token);
bool		token_is_redir(t_token *token);
bool		token_is_word(t_token *token);
char		*is_operator(char c);
char		*is_squote(char c);
char		*is_dquote(char c);
char		*is_dollar_char(char c);
bool		is_valid_var_name_char(char c);
bool		token_is_operator_token(t_token *token);
bool		token_is_redir(t_token *token);
bool		token_is_word(t_token *token);
bool		token_is_pipe(t_token *token);
bool		token_is_redir_in(t_token *token);
bool		token_is_redir_out_trunc(t_token *token);
bool		token_is_redir_out_app(t_token *token);
bool		token_is_here_doc(t_token *token);
bool		node_is_pipe(t_node *node);
bool		node_is_hdoc(t_node *node);
bool		node_is_exec(t_node *node);
bool		node_is_redir(t_node *node);

/* tokenisation/lexer 2 check syntax and get heredoc */
int			pipe_as_first_token(t_list_d *cur_token, t_token *cur_token_val);
int	operator_as_last_token(t_list_d *next_token,
							t_token *cur_token_val);
int			two_pipes_in_a_row(t_token *cur_token_val, t_token *next_token_val);
int	operator_after_operator_execpt_pipe(t_token *cur_token_val,
										t_token *next_token_val);
int			check_syntax_n_heredoc(t_main_data *main_data);
int			token_is_operator(t_token *token);
int			check_syntax(t_list_d *cur_token);
int			token_syntax_error(char *token_val);
int			check_heredoc(t_main_data *main_data, t_list_d **cur_token);
int			check_heredoc_delim(t_here_doc_info *hdoc_info);
void		init_hdoc_info(char *delim_raw, t_here_doc_info *hdoc_info);
int			copy_unquoted_chars(t_here_doc_info *hdoc_info, int i);
int			handle_quotes(t_here_doc_info *hdoc_info, int *i);
int			read_heredoc(t_here_doc_info *hdoc_info, t_list_d **hdoc_op_token);
int			parent_get_str_child(t_list_d **hdoc_op_token, int fd[2], int pid,
				t_here_doc_info *hdoc_info);
int			child_read_hdoc(t_here_doc_info *hdoc_info, int fd[2]);

bool		delimiter_entered(char *new_line, t_here_doc_info *hdoc_info);
bool		pressed_ctrl_d(char *new_line);
int			handle_eof_signaled(t_here_doc_info *hdoc_info, bool *eof,
				char **compl_str, int *str_len);
int			add_heredoc_str_token(t_list_d **hdoc_op_token, char *res,
				t_here_doc_info *hdoc_info);
int			remove_here_doc_token(t_main_data *main_data);
int			free_heredoc_info_code(t_here_doc_info *hdoc_info, int code);
bool		check_compl_str_empty(char **compl_str, int *str_len);

/* environment */

int			init_env_vars(t_main_data *main_data, char *envp[]);
int			env_del_var(t_main_data *main_data, char *val);
int			env_set_var(t_main_data *main_data, char *val);
void		env_print(t_main_data *main_data);
char		*env_get_var(t_main_data *main_data, char *key);
int			set_exit_code(int code);
int			set_program_name(void);

/* expander */

int			expand(t_main_data *main_data);
int			check_expansion(t_token *token, t_main_data *main_data);
int			expand_token_val(t_expansion_info *expansion_info);
int			expand_variable(t_expansion_info *expansion_info);
char		*get_key_env_var(t_expansion_info *expansion_info);
int			go_to_next_char(t_expansion_info *expansion_info);
int	check_for_fixed_expansions(t_expansion_info *expansion_info,
								bool *found);
int			skip_to_closing_quote(t_expansion_info *expansion_info);
int			check_dquote_start_end(t_expansion_info *expansion_info);
int			adjust_cur_pos_num(t_expansion_info *expansion_info, int num_add);
int	adjust_cur_pos_str_len(t_expansion_info *expansion_info,
							char *insert_str);
int			check_for_variable_expansions(t_expansion_info *expansion_info);
int			insert_env_var(t_expansion_info *expansion_info, char *env_var_name,
				char *key);
int	check_for_specific_fixed_expansion(t_expansion_info *expansion_info,
										bool *found,
										char *spec_var_symbol,
										char *spec_var_name);
int			remove_quote(char *cur_pos);
int			remove_empty_token(t_list_d **next);

/* parser */

int			parse(t_main_data *main_data);
bool		pipe_node_left_defined(t_node_pipe *node);
int			set_node_as_ast_root(t_parse_info *parse_info, t_node *new_node);
int			adjust_prev_nodes_ast(t_parse_info *parse_info, t_node *new_node);
int			is_first_node_of_ast(t_parse_info *parse_info);
int			set_as_root(t_parse_info *parse_info, t_node *node);
int			check_new_root_node(t_parse_info *parse_info, t_node *new_node);
int			got_to_nth_next_token(int num, t_parse_info *parse_info);
int			set_n_token_as_parsed(int num, t_parse_info *parse_info);
int			create_redir_node(t_parse_info *parse_info);
int			create_hdoc_node(t_parse_info *parse_info);
int			create_pipe_node(t_parse_info *parse_info);
int			create_exec_node(t_parse_info *parse_info);
int			add_all_but_pipe_ast(t_parse_info *parse_info, t_node *new_node);
int			add_pipe_ast(t_parse_info *parse_info, t_node_pipe *new_node);
int			set_exec_args_as_parsed(t_parse_info *parse_info);
int			append_to_last_redir(t_parse_info *parse_info, t_node *new_node);
int			change_form_of_ast(t_parse_info *parse_info);
int			init_generic_node_param(t_node *node, enum e_node_type type);
int			get_cmd_arguments(t_parse_info *parse_info, t_node_exec *exec_node);
int			copy_argument(t_node_exec *exec_node, char *new_arg);
int			got_to_nth_next_lst(t_list_d **lst, int n);
int			check_cmd_access(char **env_vars, char *cmd_arg, char **exec_path);
int			check_path_combination(char *cur_path_val, char *cmd_arg,
				char **exec_path);
int			get_path(char *envp[], char ***path);
int			check_if_cmd_exists(t_node_exec *exec_node);
int			check_if_inbuilt(t_node_exec *exec_node);
int			copy_cmd_name_to_args_arr(t_node_exec *exec_node);
int			check_if_cmd_is_folder(t_node_exec *exec_node);

/* printing for debugging */

void		print_token_list(t_list_d *token_list);
void		print_token(t_token *token);
void		print_ast(t_node *root, int depth);
int			print_redir_node(t_node_redir *node, int mode);
int			print_pipe_node(t_node_pipe *node, int mode);
int			print_hdoc_node(t_node_heredoc *node, int mode);
int			print_exec_node(t_node_exec *node, int mode);
void		print_debugging_info_executer(int on_off, int txt, void *param);

void		print_debugging_info_executer(int on_off, int txt, void *param);

/* executor */
int			navigate_tree_forward(t_main_data *data, t_node *node,
				t_pipefd *pipe_struct);
void		type_exec(t_main_data *data, t_node *node, t_pipefd *pipe_struct);
void		type_redir(t_main_data *data, t_node *node, t_pipefd *pipe_struct);
int			type_pipe(t_main_data *data, t_node *node, t_pipefd *pipe_struct);

void		type_heredoc(t_main_data *data, t_node *node,
				t_pipefd *pipe_struct);
int			executor(t_main_data *data);
void		free_ast(t_node *node);
int 		write_str_arr_pipe(int *pipefd, char **str, char *err_msg, bool is_pipe);
int 		read_str_arr_pipe(int *pipefd);
int 		write_pipe_to_executor_pipe(int *pipefd, char **str_arr, char *err_msg);


/* builtins */
// t_node_exec			*check_buildin(t_node *node);
char		**chose_buildin(t_main_data *data, t_node_exec *node,
				t_pipefd *pipe_struct);

// bool		check_is_inbuilt(t_main_data *data, t_node *node, t_pipefd *pipe_struct, int *pipefd);

bool		is_last_node_exec(t_node *node, char *path);
bool		is_last_node_redir(t_node *node, char *filename);
char		**build_pwd(bool newline);
char		**build_cd(t_main_data *data, t_node_exec *node, t_pipefd *pipefd);
char		*absoult_or_relativ_path(char *path);
char		**build_echo(t_node_exec *node);
char		**build_export(t_main_data *data, t_node_exec *node,
				t_pipefd *pipefd);
char		**build_unset(t_main_data *data, t_node_exec *node,
				t_pipefd *pipefd);
char		**build_env(t_main_data *data);
char		**build_exit(t_main_data *data, t_node_exec *node, t_pipefd *pipefd);
char		*add_newline(char *str, bool newline);
char		**copy_str_arr(char **arg, int i_beginn, bool newline);
bool		check_bash_variable(char *str);


/* execute lib*/
int			access_handler(const char *path, enum e_access_mode mode,
				int debug_mode);
void		execve_handler(const char *file_path, char **argv, char **env);
pid_t		fork_handler(char *str);
int			get_process_exit_code(int status);
void		pipe_handler(int *pipefd, char *str);
void    	*use_malloc(size_t bytes, char *err_msg);
char		*use_strjoin(char const *s1, char const *s2, char *err_msg);
char 		*use_strdup(char const *s1, char *err_msg);


//void		pipe_setting(int *pipefd, bool open, char **str, char *error_msg);
void		pipe_setting_exit_code(int *pipefd, bool open, int *exit_code, char *error_msg);
int			use_dup2(int pipefd, int fd, char *error_msg);
int			use_close(int pipefd, char *error_msg);

/* error */
int			throw_error_custom(t_error_ms error_info);
int			throw_error_mimic_bash(char *msg, int code);

char		*get_program_part_str(enum e_program_part program_part);
char		*get_failed_func_str(enum e_failed_func failed_func);

void		print_type(t_node *node);

#endif
