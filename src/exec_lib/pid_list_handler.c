/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_list_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 07:33:50 by rene              #+#    #+#             */
/*   Updated: 2024/01/22 16:42:57 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *create_node_pid_list(pid_t pid) {
    t_list *new_node = malloc(sizeof(t_list));
    pid_t *pid_ptr = malloc(sizeof(pid_t));
    if (new_node == NULL || pid_ptr == NULL) {
        free(new_node);  // Vermeidung von Speicherlecks
        free(pid_ptr);
        return NULL;
    }
    *pid_ptr = pid;
    new_node->content = pid_ptr;
    new_node->next = NULL;
    return new_node;
}

void append_node_pid_list(t_list **head, pid_t pid) {
    t_list *new_node = create_node_pid_list(pid);
    if (*head == NULL) {
        *head = new_node;
    } else {
        t_list *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void print_list_pid_list(t_list *head) {
    t_list *current = head;
    printf("PID-LIST IS: ");
    while (current != NULL) {
        pid_t *pid_ptr = (pid_t *)current->content;
        if (pid_ptr != NULL) {
            printf("%d ", *pid_ptr);
        }
        current = current->next;
    }
    printf("\n");
}

void free_list_pid_list(t_list *head) {
    t_list *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void wait_for_all_processes(t_list *pid_list) 
{
    t_list *current = pid_list;
    while (current != NULL) {
        pid_t *pid_ptr = (pid_t *)(current->content);
        if (pid_ptr != NULL) {
            waitpid(*pid_ptr, NULL, 0);
        }
        current = current->next;
    }
}
