/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:25:27 by rene              #+#    #+#             */
/*   Updated: 2024/01/20 07:48:34 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t fork_handler(void)
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
        error_code_handler(errno, "ERR-fork", " ", " ");
    return (pid);
}

enum e_pid_satus process_status(pid_t pid, bool block)
{
    int satus;
    pid_t result;
    
    if (block)
        result = (waitpid(pid, &satus, 0));
    else
        result = (waitpid(pid, &satus, WNOHANG));
    if (result < 0)
    {
        error_code_handler(errno, "ERR-waitpid", " ", " ");
        return (PID_ERROR);
    }
    if (WIFEXITED(satus))
        return PID_STOP_REGULAR;
    if (WIFSIGNALED(satus))
        return PID_STOP_SIGNAL;
    if (WIFSTOPPED(satus))
        return PID_BREAK;
    return PID_RUNNING;
}

t_pid_list *init_pid_list(t_pid_list *list)
{
    t_pid_list *ret_list;
    
    if (list == NULL)
    {
        ret_list = malloc_handler(sizeof(t_pid_list));
        ret_list->pid_list = malloc_handler(sizeof(t_list_dc));
        ret_list->pid_list->prev = NULL;
        ret_list->pid_list->next = NULL;
        return (ret_list);
    }
    
    return (list);
}