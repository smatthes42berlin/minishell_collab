/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_typedef.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:01:01 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/16 17:22:38 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPEDEF_H
# define MINISHELL_TYPEDEF_H

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
	t_list_dc			*env_vars;
	t_list_dc			*token_list;
	t_list_dc			*ast;
	char				*cli_input;
	//.....
}						t_main_data;

/**
 * describing all the possible token types,
	that can be provided by user input
 * @param TEXT normal text without any quotes: Hello
 * @param SQTEXT text in single quotes: 'Hello World'
 * @param DQTEXT text in double quotes: "Hello $0"
 * @param SYMBOL special control character of the shell, e.g. "|" :">""
 */
enum					e_token_type
{
	TEXT,
	SQTEXT,
	DQTEXT,
	SYMBOL
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

enum e_access_mode 
{
	FILE_EXISTS = F_OK,
	FILE_READABLE = R_OK,
	FILE_WRITABLE = W_OK,
	FILE_EXECUTABLE = X_OK
};

typedef enum e_open_mode
{
	FILE_ONLY_READING = O_RDONLY,
	FILE_ONLY_WRITE = O_WRONLY | O_TRUNC,
	FILE_ONLY_WRITE_APPEND = O_WRONLY | O_APPEND,
	FILE_READ_WRITE = O_RDWR | O_TRUNC,
	FILE_READ_WRITE_APPEND = O_RDWR | O_TRUNC | O_APPEND
}	t_en_open_mode;

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
 * generic serving as a prototype for every specific node type
 * @param type type identifying the node
 *
 */
typedef struct s_node
{
	enum e_node_type	type;
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
	char				*delimiter;
	t_node				*child_node;
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
	t_node				*child_node;
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
	char				*file_path;
	// handle inbuilt
	char				**argv;
	char				**env;
}						t_node_exec;

#endif
