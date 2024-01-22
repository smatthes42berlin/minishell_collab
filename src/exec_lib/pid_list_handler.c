/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_list_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 07:33:50 by rene              #+#    #+#             */
/*   Updated: 2024/01/22 08:50:29 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_list *create_node(pid_t pid) {
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

void append_node(t_list **head, pid_t pid) {
    t_list *new_node = create_node(pid);
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


void print_list(t_list *head) {
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


void free_list(t_list *head) {
    t_list *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

t_list *create_node_clone(void *data) {
    t_list *new_node = malloc(sizeof(t_list));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->content = data;  // Direkte Zuweisung von void*
    new_node->next = NULL;
    return new_node;
}

t_list *clone_list(t_list *original) {
    if (original == NULL) return NULL;

    t_list *cloned_head = NULL, **ptr = &cloned_head;

    while (original != NULL) {
        *ptr = create_node_clone(original->content);
        if (*ptr == NULL) {  // Fehlerbehandlung
            free_list(cloned_head);  // Freigabe aller bisher geklonten Knoten
            return NULL;
        }
        original = original->next;
        ptr = &((*ptr)->next);
    }

    return cloned_head;
}

