/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:43:31 by rene              #+#    #+#             */
/*   Updated: 2024/01/20 19:20:35 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node_exec *test_cmd_exec(char *command, char *commandname, char *flag)
{
    t_node_exec *exec;
    char *args1[3]; 
    
    exec = malloc_handler(sizeof(t_node_exec));
    exec->type = EXEC;
    exec->name_exec = commandname;
    exec->file_path = command;
    args1[0] = command;
    args1[2] = NULL;
    if (flag == NULL)
        args1[1] = NULL;
    else
        args1[1] = flag;
    size_t argc = 0;
    while (args1[argc] != NULL)
        argc++;
    exec->argv = malloc_handler((argc + 1) * sizeof(char*));
    for (size_t i = 0; i < argc; i++) {
        exec->argv[i] = args1[i];
    }
    exec->argv[argc] = NULL;
    char *env[] = {"PATH=/bin", NULL};
    exec->argv[argc] = NULL; 
    size_t envc = sizeof(env) / sizeof(env[0]);
    exec->env = malloc_handler(envc * sizeof(char*));
    for (size_t i = 0; i < envc; i++) {
        exec->env[i] = env[i];
    }
    return (exec);
}


t_node_pipe *test_cmd_pipe(char *name, enum e_node_type type_left, enum e_node_type type_right, void *node_left, void *node_right)
{
    t_node_pipe *pipe;
    pipe = malloc_handler(sizeof(t_node_pipe));
    pipe->type = PIPE;
    pipe->name_Pipe = name;
    pipe->left_node = malloc_handler(sizeof(t_node));
    pipe->left_node->node_type = node_left;
    pipe->left_node->type = type_left;
    pipe->right_node = malloc_handler(sizeof(t_node));
    pipe->right_node->node_type = node_right;
    pipe->right_node->type = type_right;
    return (pipe);
}