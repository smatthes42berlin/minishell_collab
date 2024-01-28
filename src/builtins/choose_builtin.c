#include "minishell.h"

bool str_equal(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (*s1 == *s2);
}

t_node_exec *check_buildin(t_node *node)
{
    t_node_exec	*exec_node;

    if (node->type != EXEC)
        return (NULL);
    exec_node = (t_node_exec *)node->node_type;
    if (exec_node->inbuild == false)
        return (NULL);
    return (exec_node);
}

char    *chose_buildin(t_node_exec *node)
{
    if (str_equal(node->file_path, "pwd"))
    {
        return(build_pwd());
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