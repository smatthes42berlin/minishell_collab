#include "minishell.h"

// singel command
t_node_exec	*set_cmd_1(void)
{
	t_node_exec	*ret;

	ret = test_cmd_exec("/bin/ls", "-l", false);
	ret->type = EXEC;
	return (ret);
}

// double command exeample "cmd | cmd"
t_node_pipe	*set_cmd_2(void)
{
	t_node_pipe	*ret;
	t_node_exec *exec_left = test_cmd_exec("/usr/bin/ls", "-l", false);
	t_node_exec *exec_rigt = test_cmd_exec( "/usr/bin/grep", ".c", false);


	//ret = malloc_handler(sizeof(t_node_pipe));
	ret = test_cmd_pipe( EXEC, EXEC,
		exec_left, 
		exec_rigt);
	ret->type = PIPE;

	print_exec_node(exec_left, 1);
	print_exec_node(exec_rigt, 1);
	return (ret);
}
// 
// t_node	*set_cmd_2_cp(void)
// {
	// t_node	*ret;
// 
	// ret->node_type = test_cmd_pipe(EXEC, EXEC,
						// test_cmd_exec( "pwd", NULL, true), 
						// test_cmd_exec("/bin/ls", "-l", false));
	// ret->type = PIPE;
	// return (ret);
// }
// 
// tree command exeample "cmd | cmd | cmd"
// t_node	*set_cmd_3(void)
// {
	// t_node	*ret;
// 
	// ret = malloc_handler(sizeof(t_node));
	// ret->node_type = test_cmd_pipe( EXEC, PIPE,
			// test_cmd_exec("/bin/sleep", "2", false), test_cmd_pipe("Pipe 2",
				// EXEC, EXEC, test_cmd_exec( "/bin/ls", "-l", false),
				// test_cmd_exec( "/bin/wc", "-l", false)));
	// ret->type = PIPE;
	// return (ret);
// }
// 
// tree command exeample "cmd | cmd | cmd | cmd"
// t_node	*set_cmd_4(void)
// {
	// t_node	*ret;
// 
	// ret = malloc_handler(sizeof(t_node));
	// ret->node_type = test_cmd_pipe( EXEC, PIPE,
			// test_cmd_exec( "/bin/sleep", "2", false), test_cmd_pipe(
				// EXEC, PIPE, test_cmd_exec( "/bin/ls", "-l", false),
				// test_cmd_pipe( EXEC, EXEC, test_cmd_exec(
						// "/bin/grep", ".c", false), test_cmd_exec(
						// "/bin/sort", "-r", false))));
	// ret->type = PIPE;
	// return (ret);
// }
// 
// //tree on redir + command
// t_node	*set_redir_in_1(void)
// {
	// t_node	*ret;
// 
	// ret = malloc_handler(sizeof(t_node));
	// ret->node_type = test_cmd_redir("input", FILE_ONLY_READING, STDIN,
			// EXEC, test_cmd_exec("/bin/grep", "nn", false));
	// ret->type = REDIR;
	// return (ret);
// }
// 
// t_node	*set_redir_in_1_cmd_2(void)
// {
	// t_node	*ret;
// 
	// ret = malloc_handler(sizeof(t_node));
	// ret->node_type = test_cmd_pipe( REDIR, PIPE,
			// test_cmd_redir("input", FILE_ONLY_READING, STDIN, EXEC,
				// test_cmd_exec( "/bin/grep", "nn", false)),
			// test_cmd_pipe(EXEC, EXEC, test_cmd_exec(
					// "/bin/uniq", NULL, false), test_cmd_exec("/usr/bin/sort",
					// NULL, false)));
	// ret->type = PIPE;
	// return (ret);
// }
// 
// t_node	*set_redir_in_2_cmd_2(void)
// {
// 	t_node	*ret;

// 	ret = malloc_handler(sizeof(t_node));
// 	ret->node_type = test_cmd_pipe( REDIR, PIPE,
// 			test_cmd_redir( "input_befor",,  STDIN, REDIR,
// 				test_cmd_redir( "input", FILE_ONLY_READING, STDIN, EXEC,
// 					test_cmd_exec("exec 1", "/bin/grep", "nn", false))),
// 			test_cmd_pipe("pipe 2", EXEC, EXEC, test_cmd_exec("exec 2",
// 					"/bin/sort", NULL, false), test_cmd_exec("exec 3", "/bin/uniq",
// 					NULL, false)));
// 	ret->type = PIPE;
// 	return (ret);
// }
// 
// tree on redir + command
// t_node	*set_redir_out_1_append(void)
// {
	// t_node	*ret;
// 
	// ret = malloc_handler(sizeof(t_node));
	// ret->node_type = test_cmd_redir("redir", "out", FILE_ONLY_WRITE_APPEND,
			// STDOUT, EXEC, test_cmd_exec("ls", "/bin/ls", "-l", false));
	// ret->type = REDIR;
	// return (ret);
// }
// 
// t_node	*set_redir_out_1(void)
// {
	// t_node	*ret;
// 
	// ret = malloc_handler(sizeof(t_node));
	// ret->node_type = test_cmd_redir("redir", "out", FILE_ONLY_WRITE,
			// STDOUT, EXEC, test_cmd_exec("ls", "/bin/ls", "-l", false));
	// ret->type = REDIR;
	// return (ret);
// }
// 
// t_node	*set_redir_out_empty(void)
// {
	// t_node	*ret;
// 
	// ret = malloc_handler(sizeof(t_node));
	// ret->node_type = test_cmd_redir("redir", "out", FILE_ONLY_WRITE_APPEND,
			// STDOUT, NOTHING, test_cmd_exec("ls", "/bin/ls", "-l", false));
	// ret->type = REDIR;
	// return (ret);
// }
// 
// void	print_type(t_node *node)
// {
	// if (node->type == EXEC)
		// printf("EXEC; \n");
	// if (node->type == PIPE)
		// printf("PIPE; \n");
	// if (node->type == REDIR)
		// printf("REDIR; \n");
//}