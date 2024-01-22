/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:49:43 by rkost             #+#    #+#             */
/*   Updated: 2024/01/22 21:32:54 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// singel command
t_node	*set_cmd_1(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_exec("sleep", "/bin/ls", "-l");
	ret->type = EXEC;
	return (ret);
}

// double command exeample "cmd | cmd"
t_node	*set_cmd_2(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_pipe("Pipe 1", EXEC, EXEC,
						test_cmd_exec("sleep", "/bin/ls", "-l"), 
						test_cmd_exec("ls", "/bin/wc", "-l"));
	ret->type = PIPE;
	return (ret);
}

// tree command exeample "cmd | cmd | cmd"
t_node	*set_cmd_3(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_pipe("Pipe 1", EXEC, PIPE,
			test_cmd_exec("/bin/ls", "/bin/sleep", "5"), test_cmd_pipe("Pipe 2",
				EXEC, EXEC, test_cmd_exec("grep", "/bin/ls", "-l"),
				test_cmd_exec("sort", "/bin/wc", "-l")));
	ret->type = PIPE;
	return (ret);
}

// tree command exeample "cmd | cmd | cmd | cmd"
t_node	*set_cmd_4(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_pipe("Pipe 1", EXEC, PIPE,
			test_cmd_exec("/bin/ls", "/bin/sleep", "5"), test_cmd_pipe("Pipe 2",
				EXEC, PIPE, test_cmd_exec("grep", "/bin/ls", "-l"),
				test_cmd_pipe("Pipe 2", EXEC, EXEC, test_cmd_exec("grep",
						"/bin/grep", "input"), test_cmd_exec("grep",
						"/bin/sort", "-r"))));
	ret->type = PIPE;
	return (ret);
}

// tree on redir + command
t_node	*set_redir_in_1(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_redir("redir", "out", FILE_ONLY_READING, STDIN,
			EXEC, test_cmd_exec("grep", "/bin/grep", "nn"));
	ret->type = REDIR;
	return (ret);
}

t_node	*set_redir_in_1_cmd_2(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_pipe("pipe 1", REDIR, PIPE,
			test_cmd_redir("redim 1", "testfile", FILE_ONLY_READING, STDIN, EXEC,
				test_cmd_exec("Exec 1", "/bin/grep", "nn")),
			test_cmd_pipe("pipe 2", EXEC, EXEC, test_cmd_exec("exec 2",
					"/bin/sort", NULL), test_cmd_exec("exec 3", "/bin/uniq",
					NULL)));
	ret->type = PIPE;
	return (ret);
}

// tree on redir + command
t_node	*set_redir_out_1(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_redir("redir", "out", FILE_ONLY_WRITE_APPEND,
			STDOUT, EXEC, test_cmd_exec("ls", "/bin/ls", "-l"));
	ret->type = REDIR;
	return (ret);
}

void	print_type(t_node *node)
{
	if (node->type == EXEC)
		printf("EXEC; \n");
	if (node->type == PIPE)
		printf("PIPE; \n");
	if (node->type == REDIR)
		printf("REDIR; \n");
}