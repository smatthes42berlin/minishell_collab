#include "minishell.h"

t_node_exec *check_buildin(t_node *node)
{
    t_node_exec	*exec_node;

    if (node->type != EXEC)
        return (NULL);
    exec_node = (t_node_exec *)node->node_type;
    if (exec_node->inbuilt == false)
        return (NULL);
    return (exec_node);
}

char    *chose_buildin(t_node_exec *node)
{
    if (str_are_equal(node->file_path, "pwd"))
    {
        return(build_pwd());
    }
    if (str_are_equal(node->file_path, "cd"))
    {
        return(buid_cd(node));
    }
    return(NULL);
}


bool    check_and_choose_buildin(t_node *node, int *pipefd, bool open)
{
    t_node_exec	*exec_node;

    exec_node = check_buildin(node);
    if (NULL == exec_node)
        return (false);
    
    
    //printf("name %s\n", exec_node->name_exec);
    //printf("file_path %s\n\n", exec_node->file_path);
    // if (str_equal(exec_node->file_path, "pwd"))
    // {
    pipe_setting(pipefd, open, chose_buildin(exec_node));
    //}
    return (true);
}