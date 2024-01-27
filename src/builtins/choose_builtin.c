#include "minishell.h"

char *build_pwd(void)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
        error_code_handler(errno, "ERR-getcwd", "", "");
    
   // printf("Current directory: %s\n", cwd);
    return (cwd);
    //free(cwd);
}

bool str_equal(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (*s1 == *s2);
}

bool    check_and_choose_buildin(t_node *node, int *pipefd, bool open)
{
    t_node_exec	*exec_node;

    if (node->type != EXEC)
        return (false);
    
    exec_node = (t_node_exec *)node->node_type;
    if (exec_node->inbuild == false)
    {
        return (false);
    }
    //printf("name %s\n", exec_node->name_exec);
    //printf("file_path %s\n\n", exec_node->file_path);
    if (str_equal(exec_node->file_path, "pwd"))
    {
        pipe_setting(pipefd, open, build_pwd());
    }
    return (true);
}