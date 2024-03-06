#ifndef MINISHELL_TYPEDEF_H
# define MINISHELL_TYPEDEF_H

# define ADD_ENV "ADD="
# define CLR_ENV "CLR="
# define ADD_CD "CD="
# define PRINT_ENV "PRINT="
# define EXIT_CODE "EXCODE="
# define EXIT "EXITPROGRAMM"
# define CONTINUE 1
# define QUIT 2
# define INT_DEBUG 0
# define PRINT_DEBUG_1 0
# define TEST_MODE 0
# define MY_SIG_IGNORE 1
# define MY_SIG_DEFAULT 2

# define FREE_ 2

typedef struct s_node	t_node;
typedef struct s_token	t_token;

typedef struct s_main_data
{
	char				**env_vars;
	t_list_d			*token_list;
	t_node				*ast;
	char				*cli_input;
	int					num_lines;
}						t_main_data;

/* tokeniser */

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

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	bool				parsed;
}						t_token;

typedef struct s_here_doc_info
{
	t_main_data			*main_data;
	char				*delim;
	char				*delim_raw;
	char				*tmp;
	char				*compl_str;
	int					str_len;
	bool				quoted;
	int					num_char_no_quote;
	int					index_close_quote;
	int					fd[2];
	int					pid;
	int					signal_exit;
}						t_here_doc_info;

/* expander */

typedef struct s_expansion_info
{
	t_token				*cur_token;
	t_main_data			*main_data;
	bool				inside_dquotes;
	char				*cur_pos;
	int					cur_pos_index;
}						t_expansion_info;

/* parser */

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

enum					e_access_mode
{
	FILE_EXISTS = F_OK,
	FILE_READABLE = R_OK,
	FILE_WRITABLE = W_OK,
	FILE_EXECUTABLE = X_OK
};

enum					e_open_mode
{
	FILE_ONLY_READING = O_RDONLY,
	FILE_ONLY_WRITE = O_WRONLY | O_TRUNC,
	FILE_ONLY_WRITE_APPEND = O_WRONLY | O_APPEND,
};

enum					e_std_fd
{
	STDIN = STDIN_FILENO,
	STDOUT = STDOUT_FILENO
};

enum					e_node_type
{
	NOTHING,
	PIPE,
	EXEC,
	REDIR,
	HEREDOC
};

typedef struct s_node
{
	enum e_node_type	type;
	t_node				*parent_node;
	t_node				*left_node;
	t_node				*right_node;
	void				*node_type;
}						t_node;

typedef struct s_node_pipe
{
	enum e_node_type	type;
	t_node				*parent_node;
	t_node				*left_node;
	t_node				*right_node;
}						t_node_pipe;

typedef struct s_node_heredoc
{
	enum e_node_type	type;
	t_node				*parent_node;
	t_node				*left_node;
	t_node				*right_node;
	int					read_fd;
}						t_node_heredoc;

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

typedef struct s_node_exec
{
	enum e_node_type	type;
	t_node				*parent_node;
	t_node				*left_node;
	t_node				*right_node;
	char				*file_path;
	char				*file_path_org;
	bool				is_folder;
	char				**argv;
	char				**env;
	bool				is_inbuilt;
}						t_node_exec;

/* executor */

typedef struct s_pipefd_main
{
	int					*pipefd;
	bool				direction;
	int					*pipefd_exit_code;
	bool				direction_exit_code;
	t_main_data			*main_data;

}						t_pipefd;

/* error handling */

enum					e_program_part
{
	EPART_MAIN,
	EPART_ENV,
	EPART_TOKENISER,
	EPART_EXPANDER,
	EPART_PARSER,
	EPART_EXECUTOR,
	EPART_SIGNAL
};

enum					e_process_status
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
