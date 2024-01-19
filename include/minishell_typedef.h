#ifndef MINISHELL_TYPEDEF_H
# define MINISHELL_TYPEDEF_H

/**
 * necessary so we can use t_node inside the t_node struct definition
*/

typedef struct s_node	t_node;


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
	t_list_d			*env_vars;
	t_list_d			*token_list;
	t_node				*ast;
	char				*cli_input;
	//.....
}						t_main_data;

//---------------------------------------------------- enum exec beginn---------------------------------
/**
 * using for the access mode 
 * @param FILE_EXISTS
 * @param FILE_READABLE
 * @param FILE_WRITABLE
 * @param FILE_EXECUTABLE
*/
enum e_access_mode 
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
 * @param FILE_READ_WRITE
 * @param FILE_READ_WRITE_APPEND
*/
enum e_open_mode
{
	FILE_ONLY_READING = O_RDONLY,
	FILE_ONLY_WRITE = O_WRONLY | O_TRUNC,
	FILE_ONLY_WRITE_APPEND = O_WRONLY | O_APPEND,
	FILE_READ_WRITE = O_RDWR | O_TRUNC,
	FILE_READ_WRITE_APPEND = O_RDWR | O_TRUNC | O_APPEND
};


enum e_pid_satus
{
	PID_STOP_REGULAR,
	PID_STOP_SIGNAL,
	PID_BREAK,
	PID_RUNNING,
	PID_ERROR
};



typedef struct s_pid_status
{
	pid_t 				pid_nbr;
	int					pipefd[2];
	enum e_pid_satus 	pid_satus;
} 				t_pid_status;

typedef struct  s_pid_list
{
	t_list_dc	*pid_list;
}				t_pid_list;


//--------------------------------------------------enum exec end --------------------------------------

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
	T_EMPTY,
	T_ENDOFINPUT,
	T_UNDEFINED
};

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
 * @param PIPE
 * @param EXEC
 * @param REDIR
 * @param HEREDOC
 */
enum					e_node_type
{
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
	char				*name_Pipe;
	t_node				*left_node;
	t_node				*right_node;
}						t_node_pipe;

/**
 * defining a heredoc-node in the ast
 * child node execution can onlu happen, when complete herdoc file is read
 * @param type
 * @param delimiter
 * @param child_node
 *
 */
typedef struct s_node_heredoc
{
	enum e_node_type	type;
	t_node				*left_node;
	t_node				*right_node;
	char				*delimiter;
}						t_node_heredoc;

/**
 * defining a redirection-node in the ast
 * @param type
 * @param child_node the node to be executed after the redirection happened
 * @param filename the file the input is read from or written into
 * @param mode mode to open the file, e.g. O_WRONLY, O_CREATE, O_RDONLY,
	O_TRUNCATE
 * @param in_or_out change either stdin or stdout
 *
 */
typedef struct s_node_redir
{
	enum e_node_type	type;
	t_node				*left_node;
	t_node				*right_node;
	char				*filename;
	char				*name_redir;
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
	t_node				*left_node;
	t_node				*right_node;
	char				*file_path;
	char				*name_exec;
	// handle inbuilt
	bool				inbuilt;
	char				**argv;
	char				**env;
	bool				is_inbuilt;
}						t_node_exec;

#endif
