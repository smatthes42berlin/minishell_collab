/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_typedef.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:01:01 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/12 15:06:28 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPEDEF_H
# define MINISHELL_TYPEDEF_H

# include "lib_main.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_main_data
{
	t_list_dc		*token_list;
	t_list_dc		*ast;
	//.....
}					t_main_data;

enum				e_token_type
{
	TEXT,
	SQTEXT,
	DQTEXT,
	SYMBOL
};

typedef struct s_token
{
	e_token_type	type;
	char			*value;
}					t_token;

enum				e_node_type
{
	PIPE,
	EXEC,
	REDIR,
	HEREDOC
};

enum				e_std_fd
{
	STDIN = STDIN_FILENO,
	STDOUT = STDOUT_FILENO
};

typedef struct s_node
{
	e_node_type		type;
}					t_node;

typedef struct s_node_pipe
{
	e_node_type		type;
	t_node			*left_node;
	t_node			*right_node;
}					t_node_pipe;

typedef struct s_node_heredoc
{
	e_node_type		type;
	char			*delimiter;
	t_node			*child_node;
}					t_node_heredoc;

typedef struct s_node_redir
{
	e_node_type		type;
	t_node			*child_node;
	char			*filename;
	int				mode;
	e_std_fd		in_or_out;
}					t_node_redir;

/**
 * @param file_path path to file, e.g. "/usr/bin/ls"
 * when file_path == NULL -> executable not found
 * @param argv array of execname and arguments, e.g. { "ls", "-l"}
 */
typedef struct s_node_exec
{
	e_node_type		type;
	char			*file_path;
	// handle inbuilt
	char			**argv;
}					t_node_exec;

#endif
