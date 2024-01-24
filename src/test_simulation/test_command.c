#include "minishell.h"

t_node_exec *test_cmd_exec( char *name, 
                            char *command,
                            char *flag)
{
    t_node_exec *exec;
    char *args1[3]; 
    
    exec = malloc_handler(sizeof(t_node_exec));
    exec->type = EXEC;
    exec->name_exec = name;
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


t_node_pipe *test_cmd_pipe( char *name, 
                            enum e_node_type type_left,
                            enum e_node_type type_right,
                            void *node_left, 
                            void *node_right)
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

t_node_redir *test_cmd_redir(    char *name,
                                char *filename,
                                enum e_open_mode mode,
                                enum e_std_fd in_or_out,
                                enum e_node_type child_typ,
                                void *child_node)
{
    t_node_redir *redir;
    redir = malloc_handler(sizeof(t_node_redir));
    redir->type = REDIR;
    redir->name_redir = name;
    redir->filename = filename;
    redir->mode = mode;
    redir->in_or_out = in_or_out;
    redir->child_node = malloc_handler(sizeof(t_node));
    redir->child_node->type = child_typ;
    redir->child_node->node_type = child_node;
    return (redir);
}