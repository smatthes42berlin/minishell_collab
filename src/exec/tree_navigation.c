/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_navigation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:25:45 by rkost             #+#    #+#             */
/*   Updated: 2024/01/22 21:14:18 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				type_exec(t_node *node);
void				type_redim(t_node *node, t_list **pid_list);
//void				type_pipe(t_node *node);
enum e_node_type	node_type(t_node *node);


void	navigate_tree_forward(t_node *node, t_list **pid_list)
{
	t_node_pipe	*pipe_node;
		int pipefd[2];
		pid_t pid;

	// t_pid_list *cloned_pid_list;
	if (node == NULL)
		error_code_handler(1000, "ERR-tree-navigation-forward:",
			" no node found", "");
	if (node->type == PIPE)
	{
		pipe_node = (t_node_pipe *)node->node_type;
		pipe_handler(pipefd);
		pid = fork_handler();
		if (pid == 0) // Kindprozess
		{
			pipe_setting(pipefd, true);
			// if (node_type(pipe_node->left_node) == REDIR){
			// 		type_redim(pipe_node->left_node, *pid_list);
			// 	}
			// 	else if (node_type(pipe_node->left_node) == EXEC){
			// 		type_exec(pipe_node->left_node);
			// 	}
			navigate_tree_forward(pipe_node->left_node, pid_list);
		}
		else // Elternprozess
		{
			append_node_pid_list(pid_list, pid);
			pipe_setting(pipefd, false);
			// if (node_type(pipe_node->left_node) == PIPE){
			// 	navigate_tree_forward(pipe_node->left_node, pid_list);
			// }
			// // Geschachteltes Fork für den rechten Knoten
			// if (node_type(pipe_node->right_node) == REDIR ||
			// 	node_type(pipe_node->right_node) == EXEC) {
			// 	pid_t nested_pid = fork_handler();
			// 	if (nested_pid == 0) { // Geschachtelter Kindprozess
			// 		if (node_type(pipe_node->right_node) == REDIR) {
			// 			type_redim(pipe_node->right_node, *pid_list);
			// 		} else if (node_type(pipe_node->right_node) == EXEC) {
			// 			type_exec(pipe_node->right_node);
			// 		}
			// 		exit(0);
			// 	} else { // Elternprozess des geschachtelten Forks
			// 		waitpid(nested_pid, NULL, 0);
			// 	}
			// }
			// else {
			navigate_tree_forward(pipe_node->right_node, pid_list);
			//}
			// waitpid(pid, NULL, 0);
		}
	}
	else if (node->type == REDIR)
		type_redim(node, pid_list);
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

void	type_redim(t_node *node, t_list **pid_list)
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
		navigate_tree_forward(redir_node->child_node, pid_list);
	}
	else
		waitpid(pid, NULL, 0);
}

// void	type_pipe(t_node *node)
// {
// 	t_node_pipe	*pipe_node;
// 	int			pipefd[2];
// 	pid_t		pid;

// 	pipe_node = (t_node_pipe *)node->node_type;
// 	pipe_handler(pipefd);
// 	pid = fork_handler();
// 	if (pid == 0)
// 	{
// 		pipe_setting(pipefd, true);
// 		navigate_tree_forward(pipe_node->left_node);
// 	}
// 	else
// 	{
// 		pipe_setting(pipefd, false);
// 		navigate_tree_forward(pipe_node->right_node);
// 	}
// }

enum e_node_type	node_type(t_node *node)
{
	return (node->type);
}
