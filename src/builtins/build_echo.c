#include "minishell.h"

static char **set_used_arg(t_main_data *data, char **arg, bool newline);
static char *str_arr_to_str(char **str, bool newline);

char **build_echo(t_main_data *data, t_node_exec *node)
{
    char **ret;
    char **tmp_str_1;
    bool newline;

    tmp_str_1 = NULL;
    newline = false;
    print_debugging_info_executer(INT_DEBUG, 23, NULL);
    if (!ft_strcmp(node->argv[1], "-n"))
    {
        newline = true;
    }
    tmp_str_1 = set_used_arg(data, node->argv, newline);
   // print_str_arr_null(tmp_str_1);
    ret = malloc_handler(sizeof(char *) * 2);
    ret[0] = str_arr_to_str(tmp_str_1, !newline);
    ret[1] = NULL;
    free_str_arr_null(tmp_str_1);
    return(ret);
}

static int start_point(bool newline)
{
    if (newline)
        return (2);
    return (1);
}

static char **set_used_arg(t_main_data *data, char **arg, bool newline)
{
    int i_count;
    char **ret;
    char *tmp_str;
    int i_beginn;

    i_beginn = start_point(newline);
    i_count = i_beginn;
   // printf("i count |%d| -- |%d|\n", i_count, i_beginn);
    while(arg[i_count] != NULL)
        i_count++;
   // printf("i count |%d| -- |%d| Malloc size |%d|\n", i_count, i_beginn, i_count - i_beginn + 1);
    ret = malloc_handler(sizeof(char *) * (i_count - i_beginn + 1));
    ret[i_count - i_beginn] = NULL;
    i_count = i_beginn;
    while(arg[i_count] != NULL)
    {   
        if (arg[i_count][0] == '$' && arg[i_count][1] != '\0')
        {
            tmp_str = env_get_var(data, arg[i_count] + 1);
            ret[i_count-i_beginn] = ft_strdup(tmp_str);
        }
        else
            ret[i_count-i_beginn] = ft_strdup(arg[i_count]);
        i_count++;
    }
    return(ret);
}

static char *str_arr_to_str(char **str, bool newline) 
{
    size_t total_length;
    char *tmp_str;
    char *ret;
    
    total_length = 0;
    int i = 0;
    tmp_str = NULL;
    while (str[i] != NULL) 
        total_length += ft_strlen(str[i++]);
    tmp_str = malloc_handler(sizeof(char) * (total_length + i + 1));
    tmp_str[0] = '\0';
    i = 0;
    while (str[i] != NULL) 
    {
        if (str[i][0] != '\0')
        {
            ft_strlcat(tmp_str, str[i], total_length + i + 1);
            if (str[i + 1] != NULL)
                ft_strlcat(tmp_str, " ", total_length + i + 1);
        }
        i++;
    }
    ret = add_newline(tmp_str, newline);
    free(tmp_str);
    return (ret);
}
