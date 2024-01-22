/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:49:43 by rkost             #+#    #+#             */
/*   Updated: 2024/01/22 17:01:53 by rkost            ###   ########.fr       */
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
t_node *set_cmd_1(void)
{
	t_node *ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_exec("sleep", "/bin/cat", "out");
	ret->type = EXEC;
	return (ret);	
}

// double command exeample "cmd | cmd"
t_node *set_cmd_2(void) 
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
t_node *set_cmd_3(void) 
{
 	t_node *ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_pipe("Pipe 1", EXEC, PIPE, 
		test_cmd_exec("/bin/ls", "/bin/sleep", "5"),
		test_cmd_pipe("Pipe 2",  EXEC, EXEC, 
			test_cmd_exec("grep", "/bin/ls", "-l"),
			test_cmd_exec("sort", "/bin/wc", "-l")));
	ret->type = PIPE;
	return (ret);	
}

// tree command exeample "cmd | cmd | cmd | cmd"
t_node *set_cmd_4(void) 
{
 	t_node *ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_pipe("Pipe 1", EXEC, PIPE, 
		test_cmd_exec("/bin/ls", "/bin/sleep", "5"),
		test_cmd_pipe("Pipe 2",  EXEC, PIPE, 
			test_cmd_exec("grep", "/bin/ls", "-l"),
			test_cmd_pipe("Pipe 2",  EXEC, EXEC,
				test_cmd_exec("grep", "/bin/grep", "input"),
				test_cmd_exec("grep", "/bin/sort", "-r"))));
	ret->type = PIPE;
	return (ret);	
}


//tree on redir + command
t_node *set_redir_in_1(void)
{
	t_node *ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_redir("redir", "out", FILE_ONLY_READING, STDIN,
									EXEC, test_cmd_exec("grep", "/bin/grep", "nn"));
	ret->type = REDIR;
	return (ret);
}

t_node *set_redir_in_1_cmd_2(void)
{
	t_node *ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_pipe("pipe 1", REDIR, PIPE,
						test_cmd_redir("redim 1", "out", FILE_ONLY_READING, STDIN, EXEC, 
							test_cmd_exec("Exec 1", "/bin/grep", "nn")),
						test_cmd_pipe("pipe 2", EXEC, EXEC,
							test_cmd_exec("exec 2", "/bin/sort", NULL),
							test_cmd_exec("exec 3", "/bin/uniq", NULL)));
	ret->type = PIPE;
	return (ret);
}

//tree on redir + command
t_node *set_redir_out_1(void)
{
	t_node *ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_redir("redir", "out", FILE_ONLY_WRITE_APPEND, STDOUT,
									EXEC, test_cmd_exec("ls", "/bin/grep", "nn"));
	ret->type = REDIR;
	return (ret);
}


void print_type(t_node *node);
 
void list_test_use(void)
{
	pid_t pid;
	pid = fork_handler();
	if (pid == 0)
	{
				//int pipefd[2];
		t_list *pid_list;
		

		pid_list = NULL; //init_pid_list();
		//pid = fork_handler();
		
		//navigate_tree_forward(set_redir_in_1_cmd_2(), &pid_list);
		t_node *example;
		t_node *head_example;
		example = set_redir_in_1_cmd_2();
		head_example = example;
		print_type(example);
		navigate_tree_forward(example, &pid_list);
		print_type(head_example);
		navigate_tree_forward(head_example, &pid_list);
		//print_pid_list(pid_list);
		wait_for_all_processes(pid_list);
		print_list_pid_list(pid_list);
		free_list_pid_list(pid_list);
		printf("Ausfürung beendet---\n");
		//fflush(stdout);
	}
	else 
	{
		waitpid(pid, NULL, 0);
	}


}

enum e_node_type type_check(t_node *node)
{
	return (node->type);
}

void print_type(t_node *node)
{
	if (node->type == EXEC)
		printf("EXEC; \n");
	if (node->type == PIPE)
		printf("PIPE; \n");
	if (node->type == REDIR)
		printf("REDIR; \n");		
}


// void list_test_use(void)
// {
// 	//int pipefd[2];
// 	t_list *pid_list;
// 	pid_t pid;

// 	pid_list = NULL; //init_pid_list();
// 	pid = fork_handler();
// 	if (pid == 0) // Kindprozess
//     {		
// 			navigate_tree_forward(set_cmd_4(), &pid_list);
// 			//print_pid_list(pid_list);
//     }
//     else
// 	{
// 		waitpid(pid, NULL, 0);
// 	}
// 	print_list(pid_list);
// 	free_list(pid_list);
// 	printf("Ausfürung beendet\n");

// }