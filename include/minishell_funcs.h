#ifndef MINISHELL_FUNCS_H
# define MINISHELL_FUNCS_H

/* main */
void	init_main_data(t_main_data *main_data);

/* tokenisation/lexer main*/

int		tokenise(t_main_data *main_data);
void	free_token(void *token);

/* tokenisation/lexer 1 create*/

void	skip_ws(char **cur_pos);
char	*is_operator(char c);
char	*is_squote(char c);
char	*is_dquote(char c);
int		has_closing_quote(char *cli_input, char quote_type);
int		get_token(t_main_data *main_data, char **cur_pos);
int		append_token_list(t_main_data *main_data, t_token *token);
int		identify_token(char **cur_pos, t_token *token);
t_token	*create_token(void);
int		count_operators(char *cur_pos);
int		count_characters(char *cur_pos);
int		identify_operator(char **cur_pos, t_token *token);
int		create_operator_token(char **cur_pos, t_token *token);
int		create_word_token(char **cur_pos, t_token *token);
void	print_token_list(t_list_d *token_list);
void	print_token(t_token *token);
int		create_empty_token(t_main_data *main_data, t_token *token);

/* tokenisation/lexer 2 check syntax and get heredoc */

int		check_syntax_n_heredoc(t_main_data *main_data);
int		token_is_operator(t_token *token);
int		check_syntax(t_list_d *cur_token);
int		token_syntax_error(char *token_val);
int		check_heredoc(t_list_d **cur_token);
int		check_heredoc_delim(t_here_doc_info *hdoc_info);
void	init_hdoc_info(char *delim_raw, t_here_doc_info *hdoc_info);
int		copy_unquoted_chars(t_here_doc_info *hdoc_info, int i);
int		handle_quotes(t_here_doc_info *hdoc_info, int *i);
int		read_heredoc(t_here_doc_info *hdoc_info, t_list_d **hdoc_op_token);
int		parent_get_str_child(t_list_d **hdoc_op_token, int fd[2], int pid);
int		child_read_hdoc(t_here_doc_info *hdoc_info, int fd[2]);
int		add_heredoc_str_token(t_list_d **hdoc_op_token, char *res);
int		remove_here_doc_token(t_main_data *main_data);

/* parser */

int		parse(t_main_data *main_data);

/* executor */

#endif
