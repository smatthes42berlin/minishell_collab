/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_navigation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:25:45 by rkost             #+#    #+#             */
/*   Updated: 2024/01/19 17:10:28 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void navigate_tree_forward(t_node *node)
{
	if (node == NULL)
		error_code_handler(1000, "ERR-tree-navigation-forward:", " no node found", "");
	if (node->type == EXEC)
	{
		//t_node_exec *exec_node = (t_node_exec *)node->node_type;
		//printf("Exec Node: %s\n", exec_node->file_path);
			t_node_exec *exec = malloc_handler(sizeof(t_node_exec));
	exec->file_path = "/bin/ls";
	exec->argv = (char *[]){"/bin/ls", "-l", NULL}; 
	exec->env = (char *[]){"PATH=/bin", NULL};
		execve_handler(exec);
	}
	else if (node->type == REDIR)
	{
		t_node_redir *redim_node = (t_node_redir *)node->node_type;
		//Someting to du for dup2 //
		navigate_tree_forward(redim_node->child_node);
	}
	else if (node->type == PIPE)
	{
		t_node_pipe *pipe_node = (t_node_pipe *)node->node_type;
		//Someting to du for fork pipe //
		navigate_tree_forward(pipe_node->left_node);
		navigate_tree_forward(pipe_node->right_node);
	}
}