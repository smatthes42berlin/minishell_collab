#ifndef MINISHELL_TYPEDEF_H
# define MINISHELL_TYPEDEF_H

# define ADD_ENV "ADD="
# define CLR_ENV "CLR="
# define ADD_CD "CD="
# define PRINT_ENV "PRINT="
# define INT_DEBUG 0

/**
 * necessary so we can use t_node inside the t_node struct definition
*/

typedef struct s_node	t_node;
typedef struct s_token	t_token;

/**
 * main data structure, that can be passed around

	* @param env_vars pointer to first element of list containing all the avaailable environment variables of the shell,
	NULL when no env vars or uninitialised
 * @param token_list pointer to first element of token list or NULL,
	when token list is uninitialised
 * @param ast pointer to root node of abstract syntax tree (ast)
 * @param cli_input commands string enter by the user and read via readline
 */
typedef struct s_main_data
{
	char				**env_vars;
	t_list_d			*token_list;
	t_node				*ast;
	char				*cli_input;
	int					exit_code;
}						t_main_data;



/**
 * using for the access mode 
 * @param FILE_EXISTS
 * @param FILE_READABLE
 * @param FILE_WRITABLE
 * @param FILE_EXECUTABLE
*/
enum					e_access_mode
{
	FILE_EXISTS = F_OK,
	FILE_READABLE = R_OK,
	FILE_WRITABLE = W_OK,
	FILE_EXECUTABLE = X_OK
};

/**
 * using for the open mode
 * @param FILE_ONLY_READING
 * @param FILE_ONLY_WRITE
 * @param FILE_ONLY_WRITE_APPEND
*/
enum					e_open_mode
{
	FILE_ONLY_READING = O_RDONLY,
	FILE_ONLY_WRITE = O_WRONLY | O_TRUNC,
	FILE_ONLY_WRITE_APPEND = O_WRONLY | O_APPEND,
};


typedef struct s_pipefd_main
{
	int					*pipefd;
	bool				direction;
}						t_pipefd;

/**
 * describing all the possible token types,
	that can be provided by user input
 * @param TEXT normal text without any quotes: Hello
 * @param SQTEXT text in single quotes: 'Hello World'
 * @param DQTEXT text in double quotes: "Hello $0"
 * @param operator special control character of the shell, e.g. | >
 * @param EMPTY an empty single or double quoted string
 */
enum					e_token_type
{
	T_WORD,
	T_DLESS,
	T_DGREAT,
	T_LESS,
	T_GREAT,
	T_PIPE,
	T_HEREDOC,
	T_UNDEFINED
};

typedef struct s_here_doc_info
{
	char				*delim;
	char				*delim_raw;
	char				*tmp;
	bool				quoted;
	int					num_char_no_quote;
	int					index_close_quote;
}						t_here_doc_info;

typedef struct s_expansion_info
{
	t_token				*cur_token;
	t_main_data			*main_data;
	bool				inside_dquotes;
	char				*cur_pos;
	int					cur_pos_index;
}						t_expansion_info;

typedef struct s_parse_info
{
	t_list_d			*next;
	t_token				*cur_token;
	t_node				*root_node_ast;

	t_node				*ast_rene;
	t_node				*ast_steffen;
	t_node				*cur_pipe;
	t_main_data			*main_data;

}						t_parse_info;

typedef struct s_ident_token_info
{
	enum e_token_type	token_type;
	char				*token_value;
	char				**cur_pos;
	t_token				*token;
}						t_ident_token_info;

/**
 * generic for an identified token
 * @param type
 * @param value
 *
 */
typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	bool				parsed;
}						t_token;

/**
 * describing the filedescritors available for input output redirection
 * @param STDIN
 * @param STDOUT
 */
enum					e_std_fd
{
	STDIN = STDIN_FILENO,
	STDOUT = STDOUT_FILENO
};

/**
 * describing all the possible node types within the ast
 * @param NOTHING    for redim e.g. > out 
 * @param PIPE
 * @param EXEC
 * @param REDIR
 * @param HEREDOC
 */
enum					e_node_type
{
	NOTHING,
	PIPE,
	EXEC,
	REDIR,
	HEREDOC
};

/**
 * generic serving as a prototype for every specific node type
 * @param type type identifying the node
 *
 */
typedef struct s_node
{
	enum e_node_type	type;
	t_node				*parent_node;
	t_node				*left_node;
	t_node				*right_node;
	void				*node_type;
}						t_node;

/**
 * defining a pipe-node in the ast
 * @param type
 * @param left_node
 * @param right_node
 *
 */
typedef struct s_node_pipe
{
	enum e_node_type	type;
	t_node				*parent_node;
	t_node				*left_node;
	t_node				*right_node;
}						t_node_pipe;

/**
 * defining a heredoc-node in the ast
 * child node execution can onlu happen, when complete herdoc file is read
 * @param type
 * @param delimiter
 * @param left_node
 *
 */
typedef struct s_node_heredoc
{
	enum e_node_type	type;
	t_node				*parent_node;
	t_node				*left_node;
	t_node				*right_node;
	int					read_fd;
}						t_node_heredoc;

/**
 * defining a redirection-node in the ast
 * @param type
 * @param left_node the node to be executed after the redirection happened
 * @param filename the file the input is read from or written into
 * @param mode mode to open the file, e.g. O_WRONLY, O_CREATE, O_RDONLY,
	O_TRUNCATE
 * @param in_or_out change either stdin or stdout
 *
 */
typedef struct s_node_redir
{
	enum e_node_type	type;
	t_node				*parent_node;
	t_node				*left_node;
	t_node				*right_node;
	char				*filename;
	enum e_open_mode	mode;
	enum e_std_fd		in_or_out;
}						t_node_redir;

/**
 * @param file_path path to file, e.g. "/usr/bin/ls"
 * when file_path == NULL -> executable not found
 * @param argv array of execname and arguments, e.g. { "ls", "-l"}
 */
typedef struct s_node_exec
{
	enum e_node_type	type;
	t_node				*parent_node;
	t_node				*left_node;
	t_node				*right_node;
	char				*file_path;
	char				**argv;
	char				**env;
	bool				is_inbuilt;
}						t_node_exec;

/* error handling */

enum					e_program_part
{
	EPART_MAIN,
	EPART_ENV,
	EPART_TOKENISER,
	EPART_EXPANDER,
	EPART_PARSER,
	EPART_EXECUTOR,
};


/**
 * @brief Show in which state a child process end! 
 * 
 * @PROCESS_EXITED 				--> Process exited normally (e.g., 
 * 									via exit() or returning from main())
 * @PROCESS_KILLED_BY_SIGINT	--> Process was terminated by the SIGINT
 * 									signal (e.g., pressing Ctrl+C)
 * @PROCESS_KILLED_BY_SIGSEGV	--> Process was terminated by the SIGSEGV
 * 									signal (e.g., due to a segmentation fault)
 * @PROCESS_KILLED_BY_SIGTERM	--> Process was terminated by the SIGTERM signal
 * 									(e.g., a polite request to terminate)
 * @PROCESS_KILLED_BY_SIGQUIT	--> Process was terminated by the SIGQUIT
 * 									signal (e.g., pressing Ctrl+\)
 * @PROCESS_KILLED_OTHER		--> Process was terminated by another 
 * 									signal not specified here
 * @PROCESS_STOPPED				--> Process was stopped (e.g., by the
 * 									SIGSTOP signal)
 * @PROCESS_CONTINUED			--> Process was continued (e.g., after
 * 									being stopped by SIGSTOP, continued with SIGCONT)
 */

enum				e_process_status 
{
	PROCESS_EXITED,
	PROCESS_KILLED_BY_SIGINT,
	PROCESS_KILLED_BY_SIGSEGV,
	PROCESS_KILLED_BY_SIGTERM,
	PROCESS_KILLED_BY_SIGQUIT,
	PROCESS_KILLED_OTHER,
	PROCESS_STOPPED,
	PROCESS_CONTINUED
};

enum					e_failed_func
{
	EFUNC_DEV_ISSUE,
	EFUNC_INPUT_ERROR,
	EFUNC_RL_CLEAR_HISTORY,
	EFUNC_RL_ON_NEW_LINE,
	EFUNC_RL_REPLACE_LINE,
	EFUNC_RL_REDISPLAY,
	EFUNC_ADD_HISTORY,
	EFUNC_PRINTF,
	EFUNC_MALLOC,
	EFUNC_FREE,
	EFUNC_WRITE,
	EFUNC_ACCESS,
	EFUNC_OPEN,
	EFUNC_READ,
	EFUNC_CLOSE,
	EFUNC_FORK,
	EFUNC_WAIT,
	EFUNC_WAITPID,
	EFUNC_WAIT3,
	EFUNC_WAIT4,
	EFUNC_SIGNAL,
	EFUNC_SIGACTION,
	EFUNC_SIGEMPTYSET,
	EFUNC_SIGADDSET,
	EFUNC_KILL,
	EFUNC_EXIT,
	EFUNC_GETCWD,
	EFUNC_CHDIR,
	EFUNC_STAT,
	EFUNC_LSTAT,
	EFUNC_FSTAT,
	EFUNC_UNLINK,
	EFUNC_EXECVE,
	EFUNC_DUP,
	EFUNC_DUP2,
	EFUNC_PIPE,
	EFUNC_OPENDIR,
	EFUNC_READDIR,
	EFUNC_CLOSEDIR,
	EFUNC_STRERROR,
	EFUNC_PERROR,
	EFUNC_ISATTY,
	EFUNC_TTYNAME,
	EFUNC_TTYSLOT,
	EFUNC_IOCTL,
	EFUNC_GETENV,
	EFUNC_TCSETATTR,
	EFUNC_TCGETATTR,
	EFUNC_TGETENT,
	EFUNC_TGETFLAG,
	EFUNC_TGETNUM,
	EFUNC_TGETSTR,
	EFUNC_TGOTO,
	EFUNC_TPUTS
};

typedef struct s_error_ms
{
	int					err_code;
	enum e_program_part	program_part;
	enum e_failed_func	failed_func;
	char				*add_info;
}						t_error_ms;

#endif
