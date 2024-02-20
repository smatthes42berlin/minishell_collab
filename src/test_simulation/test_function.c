#include "minishell.h"

// // singel command
// t_node_exec	*set_cmd_1(void)
// {
// 	t_node_exec	*ret;

// 	ret = test_cmd_exec("/bin/ls", "-l", false);
// 	ret->type = EXEC;
// 	return (ret);
// }

// // double command exeample "cmd | cmd"
// t_node_pipe	*set_cmd_2(void)
// {
// 	t_node_pipe	*ret;
// 	t_node_exec *exec_left = test_cmd_exec("/usr/bin/ls", "-l", false);
// 	t_node_exec *exec_rigt = test_cmd_exec( "/usr/bin/grep", ".c", false);


// 	//ret = malloc_handler(sizeof(t_node_pipe));
// 	ret = test_cmd_pipe( EXEC, EXEC,
// 		exec_left, 
// 		exec_rigt);
// 	ret->type = PIPE;

// 	print_exec_node(exec_left, 1);
// 	print_exec_node(exec_rigt, 1);
// 	return (ret);
// }
