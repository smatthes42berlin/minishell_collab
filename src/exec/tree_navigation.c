/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_navigation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:25:45 by rkost             #+#    #+#             */
/*   Updated: 2024/01/20 11:15:12 by rene             ###   ########.fr       */
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
		printf("----i am at the PIPE %s\n", pipe_node->name_Pipe);
        fflush(stdout);
        // Erstellen eines neuen Prozesses für den linken Teil der Pipe
        pid = fork_handler();
        if (pid == 0) // Kindprozess
        {
            // Umleiten der Standardausgabe zum Schreiben in die Pipe
            pipe_setting(pipefd, true);
            navigate_tree_forward(pipe_node->left_node);
            //exit(0); // Beenden des Kindprozesses
        }
        else // Elternprozess
        {
            // Umleiten der Standardeingabe zum Lesen aus der Pipe
            // int status;
            // waitpid(pid, &status, 0);
            pipe_setting(pipefd, false);
            navigate_tree_forward(pipe_node->right_node);
        }
        // t_node_pipe *pipe_node = (t_node_pipe *)node->node_type;
		// printf("----i am at the PIPE %s\n", pipe_node->name_Pipe);
        // t_pid_status *pid_status;
		// //pid_list = malloc_handler(sizeof(t_list_dc));
		// pid_status = malloc_handler(sizeof(t_pid_status));
		
	    // // Erstellen der Pipe
        // pipe_handler(pid_status->pipefd);
        // pid_status->pid_nbr = fork_handler();
        // if (pid_status->pid_nbr == 0) // Kindprozess
        // {

		// 	if (pipe_node->left_node->type == EXEC)
		// 		printf("EXEC erkkannt!\n");
		// 	else if (pipe_node->left_node->type == PIPE)
		// 		printf("PIPE erkkannt!\n");
		// 	else if (pipe_node->left_node->type == REDIR)
		// 		printf("REDIR erkkannt!\n");

		// 	pipe_setting(pid_status->pipefd, true);
        //     navigate_tree_forward(pipe_node->left_node);
        //     exit(0); // Beenden des Kindprozesses
        // }
        // else // Elternprozess
        // {
		// 	int status;
		// 	waitpid(pid_status->pid_nbr, &status, 0);
        //     pipe_setting(pid_status->pipefd, false);
        //     navigate_tree_forward(pipe_node->right_node);
        // }
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
		//printf("i am at the EXEC %s\n", exec_node->name_exec);
		printf("Exec Node: %s\n", exec_node->file_path);
        fflush(stdout);
		execve_handler(exec_node);
	}
    else 
        printf("No Nodetype found\n");
}

// void pid_nbr_handler(t_pid_status *pid_satus)
// {
	
// }