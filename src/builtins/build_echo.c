#include "minishell.h"

static char **check_arg(t_main_data *data, char **arg);
static char *str_arr_to_str(char **str);

char **build_echo(t_main_data *data, t_node_exec *node)
{
    char **ret;
    char **tmp_str_1 = NULL;

    print_debugging_info_executer(INT_DEBUG, 23, NULL);
    tmp_str_1 = check_arg(data, node->argv);
    ret = malloc_handler(sizeof(char *) * 2);
    ret[0] = str_arr_to_str(tmp_str_1);
    ret[1] = NULL;
    //printf("Das ist das ergebniss |%s|\n", ret[0]);
    free_str_arr_null(tmp_str_1);
    //free_str_arr_null(ret);
    return(ret);
}

static char **check_arg(t_main_data *data, char **arg)
{
    int i_count;
    char **ret;
    char *tmp_str;

    i_count = 1;
    while(arg[i_count] != NULL)
        i_count++;
    ret = malloc_handler(sizeof(char *) * i_count);
    ret[i_count] = NULL;
    i_count = 1;
    while(arg[i_count] != NULL)
    {   
        if (arg[i_count][0] == '$' && arg[i_count][1] != '\0')
        {
            tmp_str = env_get_var(data, arg[i_count] + 1);
            ret[i_count-1] = ft_strdup(tmp_str);
        }
        else
            ret[i_count-1] = ft_strdup(arg[i_count]);
        i_count++;
    }
    return(ret);
}

static char *str_arr_to_str(char **str) 
{
    size_t total_length;
    char *tmp_str;
    char *ret;
    
    total_length = 0;
    int i = 0;
    tmp_str = NULL;
    while (str[i] != NULL) 
        total_length += ft_strlen(str[i++]);
    tmp_str = malloc(sizeof(char) * (total_length + i + 1));
    if (tmp_str == NULL)
        return NULL;
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
    ret = ft_strjoin(tmp_str, "\n");
    free(tmp_str);
    return (ret);
}

// //----------------------------------Test settings ------------------------

// t_node	*set_echo_singel(void)
// {
// 	t_node	*ret;

// 	ret = malloc_handler(sizeof(t_node));
// 	ret->node_type = test_cmd_exec("echo", "echo", "Das ist ein Testfile\n", true);
// 	ret->type = EXEC;
// 	return (ret);
// }

// t_node	*set_echo_option(void)
// {
// 	t_node	*ret;

// 	ret = malloc_handler(sizeof(t_node));
// 	ret->node_type = test_cmd_exec("echo", "echo", "Das ist ein Testfile", true);
// 	ret->type = EXEC;
// 	return (ret);
// }

// t_node	*set_echo_redir(void)
// {
// 	t_node	*ret;

// 	ret = malloc_handler(sizeof(t_node));

// 	ret->node_type = test_cmd_redir("redir", "out", FILE_ONLY_WRITE_APPEND, STDOUT, EXEC,
//         test_cmd_exec("echo", "echo", "Das ist ein Testfile\n", true));
// 	ret->type = REDIR;
// 	return (ret);
// }


// t_node	*set_echo_redim_cmd_2(void)
// {
// 	t_node	*ret;

// 	ret = malloc_handler(sizeof(t_node));

// 	ret->node_type = test_cmd_pipe("PIPE 1", REDIR, PIPE, 
//         test_cmd_redir("redir", "out", FILE_ONLY_WRITE_APPEND, STDOUT, EXEC,
//             test_cmd_exec("echo", "echo", "Das ist ein Testfile\n", true)),
//         test_cmd_pipe("PIPE 2", EXEC, EXEC, 
//             test_cmd_exec("ls", "/bin/ls", "-l", false), 
// 			test_cmd_exec("wc", "/bin/wc", "-l", false)));
// 	ret->type = PIPE;
// 	return (ret);
// }