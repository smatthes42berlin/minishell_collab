#include "minishell.h"

char *build_echo(t_node_exec *node)
{
    printf("I am in echo\n\n--------------------\n");
   // printf("%s\n-------\n", node->argv[1]);
    print_exec_node(node, 1);
    return(node->argv[1]);
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