/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_navigation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:25:45 by rkost             #+#    #+#             */
/*   Updated: 2024/01/22 13:28:49 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//t_pid_list *add_pid_list(t_pid_list *pid_li, pid_t pid, int pipefild[2]);
//t_pid_list *clone_pid_list(const t_pid_list *original_list);
//enum e_node_type node_type(t_node *node);

// void print_pid_list(const t_pid_list *pid_list) {
//     if (pid_list == NULL || pid_list->pid_list == NULL) {
//         printf("Die PID-Liste ist leer oder nicht initialisiert.\n");
//         return;
//     }

//     t_list_dc *current = pid_list->pid_list;
//     while (current != NULL) {
//         t_pid_status *pid_status = (t_pid_status *)current->content;
//         if (pid_status != NULL) {
//             printf("PID: %d\n", pid_status->pid_nbr);
//         }
//         current = current->next;
//     }
// }

void type_exec (t_node *node);
void type_redim (t_node *node, t_list *pid_list);
enum e_node_type node_type(t_node *node);

void navigate_tree_forward(t_node *node, t_list **pid_list)
{
    //t_pid_list *cloned_pid_list;
            
	if (node == NULL)
		error_code_handler(1000, "ERR-tree-navigation-forward:", " no node found", "");
		
    if (node->type == PIPE)
    { 
        t_node_pipe *pipe_node = (t_node_pipe *)node->node_type;
        int pipefd[2];
        pid_t pid;
        pipe_handler(pipefd);
        pid = fork_handler();

        if (pid == 0) // Kindprozess
        {
            
           pipe_setting(pipefd, true);
           if (node_type(pipe_node->left_node) == REDIR){
                type_redim(pipe_node->left_node, *pid_list);
            }
            else if (node_type(pipe_node->left_node) == EXEC){
                type_exec(pipe_node->left_node);
            }
           
            //navigate_tree_forward(pipe_node->left_node, pid_list);
        }
        else // Elternprozess
        {
            append_node(pid_list, pid);
            printf("New pid nbr: %i\n", pid);
            pipe_setting(pipefd, false);
            if (node_type(pipe_node->left_node) == PIPE){
                navigate_tree_forward(pipe_node->left_node, pid_list);
            }
            // Geschachteltes Fork für den rechten Knoten
            if (node_type(pipe_node->right_node) == REDIR || 
                node_type(pipe_node->right_node) == EXEC) {
                pid_t nested_pid = fork_handler();

                if (nested_pid == 0) { // Geschachtelter Kindprozess
                    if (node_type(pipe_node->right_node) == REDIR) {
                        type_redim(pipe_node->right_node, *pid_list);
                    } else if (node_type(pipe_node->right_node) == EXEC) {
                        type_exec(pipe_node->right_node);
                    }
                    exit(0);
                } else { // Elternprozess des geschachtelten Forks
                    waitpid(nested_pid, NULL, 0);
                }
            } 
            else {
                navigate_tree_forward(pipe_node->right_node, pid_list);
            }
            

            //free(cloned_list);
        }
        
    }
	else if (node->type == REDIR)
        type_redim(node, *pid_list);
    else if (node->type == EXEC)
        type_exec(node);
	// {
	// 	t_node_exec *exec_node = (t_node_exec *)node->node_type;
	// 	execve_handler(exec_node);
	// }
    else 
        printf("No Nodetype found\n");
    //print_list(*pid_list);
}

void type_exec (t_node *node)
{
    t_node_exec *exec_node = (t_node_exec *)node->node_type;
	execve_handler(exec_node);
}

void type_redim (t_node *node, t_list *pid_list)
{
    t_node_redir *redir_node = (t_node_redir *)node->node_type;
    pid_t pid;
    int fd;
    pid = fork_handler();
    if (pid == 0)
    {
        fd = open_handler(redir_node->filename,redir_node->mode);
        dup2(fd, redir_node->in_or_out);
        close(fd);
        navigate_tree_forward(redir_node->child_node, &pid_list);
    }
    else
    {
        waitpid(pid, NULL, 0);
    }  
}

enum e_node_type node_type(t_node *node)
{
    return(node->type);
}


/**



// t_pid_list *add_pid_list(t_pid_list *pid_li, pid_t pid, int pipefild[2])
// {
//     t_pid_status *pid_satus;
//     t_list_dc *new_node;
//     t_list_dc *last;
    
    
//     pid_satus = malloc_handler(sizeof(t_pid_status));
//     pid_satus->pid_nbr = pid;
//     ft_memcpy(pid_satus->pipefd, pipefild, sizeof(pid_satus->pipefd));
    
//     new_node = malloc_handler(sizeof(t_list_dc));
//     new_node->content = pid_satus;
//     new_node->next = NULL;
//     new_node->prev = NULL;

//     if (pid_li->pid_list == NULL)
//         pid_li->pid_list = new_node;
//     else 
//     { 
//         last = pid_li->pid_list;
//         while (last->next != NULL)
//             last = last->next;  
//         last->next = new_node;
//         new_node->prev = last;
//     }
//             printf("Add pid list %i\n", pid);
//     return (pid_li);
    
// }

// t_pid_status *clone_pid_status(const t_pid_status *original) {
//     if (original == NULL) {
//         return NULL;
//     }

//     t_pid_status *new_status = malloc(sizeof(t_pid_status));
//     if (new_status == NULL) {
//         return NULL; // Fehlerbehandlung
//     }

//     new_status->pid_nbr = original->pid_nbr;
//     new_status->pipefd[0] = original->pipefd[0];
//     new_status->pipefd[1] = original->pipefd[1];
//     new_status->pid_satus = original->pid_satus;

//     return new_status;
// }


// t_pid_list *clone_pid_list(const t_pid_list *original_list) {
//     if (original_list == NULL || original_list->pid_list == NULL) {
//         return NULL;
//     }

//     t_pid_list *new_list = malloc(sizeof(t_pid_list));
//     if (new_list == NULL) {
//         return NULL; // Fehlerbehandlung
//     }

//     t_list_dc *current_old = original_list->pid_list;
//     t_list_dc *current_new = NULL;
//     t_list_dc *prev_new = NULL;

//     while (current_old != NULL) {
//         current_new = malloc(sizeof(t_list_dc));
//         if (current_new == NULL) {
//             // Hier sollte der Speicher von new_list und allen bisher erstellten Knoten freigegeben werden
//             return NULL; // Fehlerbehandlung
//         }

//         current_new->content = clone_pid_status((t_pid_status *)current_old->content);
//         current_new->next = NULL;
//         current_new->prev = prev_new;
        
//         if (prev_new != NULL) {
//             prev_new->next = current_new;
//         } else {
//             new_list->pid_list = current_new; // Setze den Kopf der neuen Liste
//         }

//         prev_new = current_new;
//         current_old = current_old->next;
//     }

//     return new_list;
// }

*/
