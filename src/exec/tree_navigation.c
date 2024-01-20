/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_navigation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:25:45 by rkost             #+#    #+#             */
/*   Updated: 2024/01/20 19:22:15 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void navigate_tree_forward(t_node *node)
{
	if (node == NULL)
		error_code_handler(1000, "ERR-tree-navigation-forward:", " no node found", "");
		
    if (node->type == PIPE)
    {

        t_node_pipe *pipe_node = (t_node_pipe *)node->node_type;
        int pipefd[2];
        pid_t pid;

        // Erstellen der Pipe
        pipe_handler(pipefd);
		//printf("----i am at the PIPE %s\n", pipe_node->name_Pipe);
       // fflush(stdout);
        pid = fork_handler();
        if (pid == 0) // Kindprozess
        {
            pipe_setting(pipefd, true);
            navigate_tree_forward(pipe_node->left_node);
            exit(0); // Beenden des Kindprozesses
        }
        else // Elternprozess
        {
            // int status;
            // waitpid(pid, &status, 0);
            pipe_setting(pipefd, false);
            navigate_tree_forward(pipe_node->right_node);
        }
    }
	else if (node->type == REDIR)
	{
		printf("i am at the REDIR\n");
		t_node_redir *redim_node = (t_node_redir *)node->node_type;
		//Someting to du for dup2 //
		navigate_tree_forward(redim_node->child_node);
	}
    else if (node->type == EXEC)
	{
		t_node_exec *exec_node = (t_node_exec *)node->node_type;
		//printf("Exec Node: %s\n", exec_node->file_path);
        fflush(stdout);
		execve_handler(exec_node);
	}
    else 
        printf("No Nodetype found\n");
}

// void pid_nbr_handler(t_pid_status *pid_satus)
// {
	
// }