/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_navigation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:25:45 by rkost             #+#    #+#             */
/*   Updated: 2024/01/22 20:05:32 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				type_exec(t_node *node);
void				type_redim(t_node *node);
void				type_pipe(t_node *node);
enum e_node_type	node_type(t_node *node);

void	navigate_tree_forward(t_node *node)
{
	if (node == NULL)
		error_code_handler(1000, "ERR-tree-navigation-forward:",
			" no node found", "");
	if (node->type == PIPE)
		type_pipe(node);
	else if (node->type == REDIR)
		type_redim(node);
	else if (node->type == EXEC)
		type_exec(node);
	else
	{
		printf("No Nodetype found\n");
	}
}

void	type_exec(t_node *node)
{
	t_node_exec	*exec_node;
	char		*file_path;
	char		**argv;
	char		**env;

	exec_node = (t_node_exec *)node->node_type;
	file_path = exec_node->file_path;
	argv = exec_node->argv;
	env = exec_node->env;
	free(node);
	execve_handler(file_path, argv, env);
}

void	type_redim(t_node *node)
{
	t_node_redir	*redir_node;
	pid_t			pid;
	int				fd;

	redir_node = (t_node_redir *)node->node_type;
	pid = fork_handler();
	if (pid == 0)
	{
		fd = open_handler(redir_node->filename, redir_node->mode);
		dup2(fd, redir_node->in_or_out);
		close(fd);
		navigate_tree_forward(redir_node->child_node);
	}
	else
		waitpid(pid, NULL, 0);
}

void	type_pipe(t_node *node)
{
	t_node_pipe	*pipe_node;
	int			pipefd[2];
	pid_t		pid;

	pipe_node = (t_node_pipe *)node->node_type;
	pipe_handler(pipefd);
	pid = fork_handler();
	if (pid == 0)
	{
		pipe_setting(pipefd, true);
		navigate_tree_forward(pipe_node->left_node);
	}
	else
	{
		pipe_setting(pipefd, false);
		navigate_tree_forward(pipe_node->right_node);
	}
}

enum e_node_type	node_type(t_node *node)
{
	return (node->type);
}
