/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:49:43 by rkost             #+#    #+#             */
/*   Updated: 2024/01/20 20:57:43 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_read(void)
{
	t_node_redir redir;
	redir.filename = "/home/rkost/Project/Rank03/minishell_collab/src/exec/readme_test.txt";
	redir.in_or_out = STDIN;
	redir.mode = FILE_ONLY_READING;

	int fd;
    char buffer[100];
    ssize_t bytesRead;
	
	fd = open_handler(redir.filename, FILE_ONLY_READING);
	
	while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0';
        printf("%s", buffer);
    }

    if (bytesRead == -1) {
        perror("Fehler beim Lesen der Datei");
        close(fd);
        return ;
    }

	close_handler(fd);	
}

// singel command 
t_node *set_test_list (void)
{
	t_node *ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_exec("sleep", "/bin/cat", "out");
	ret->type = EXEC;
	return (ret);	
}

// double command exeample "cmd | cmd"
t_node *set_test_list_2(void) 
{
 	t_node *ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_pipe("Pipe 1", EXEC, EXEC, 
		test_cmd_exec("sleep", "/bin/sleep", "5"), 
		test_cmd_exec("ls", "/bin/ls", "-l"));
	ret->type = PIPE;
	return (ret);	
}

// tree command exeample "cmd | cmd | cmd"
t_node *set_test_list_3(void) 
{
 	t_node *ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_pipe("Pipe 1", EXEC, PIPE, 
		test_cmd_exec("/bin/ls", "ls-cmd", "-l"),
		test_cmd_pipe("Pipe 2",  EXEC, EXEC, 
			test_cmd_exec("grep", "/bin/grep", "input"),
			test_cmd_exec("sort", "/bin/sort", NULL)));
	ret->type = PIPE;
	return (ret);	
}

//tree on redir + command
t_node *set_test_list_redir(void)
{
	t_node *ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_redir("redir", "out", FILE_ONLY_READING, STDIN,
									EXEC, test_cmd_exec("grep", "/bin/grep", "nn"));
	ret->type = REDIR;
	return (ret);
}

void list_test_use(void)
{
	//int pipefd[2];
    pid_t pid;

	pid = fork_handler();
	if (pid == 0) // Kindprozess
    {		
			navigate_tree_forward(set_test_list_redir());
    }
    else
	{
		wait(NULL);
	}
	printf("Ausfürung beendet\n");
}