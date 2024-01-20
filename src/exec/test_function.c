/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:49:43 by rkost             #+#    #+#             */
/*   Updated: 2024/01/20 11:16:22 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_main_data_test(t_main_data *main_data)
{
	main_data->ast = NULL;
	main_data->cli_input = NULL;
	main_data->env_vars = NULL;
	main_data->token_list = NULL;
}

// void	test_exece(void)
// {
// 	t_node_exec *exec = malloc_handler(sizeof(t_node_exec));
// 	exec->file_path = "/bin/ls";
// 	exec->argv = (char *[]){"/bin/ls", "-l", NULL}; 
// 	exec->env = (char *[]){"PATH=/bin", NULL};
// 	execve_handler(exec);
// }

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

t_node *set_test_list(void) {
    // Initialisierung von exec_node1
    t_node_exec *exec_node1 = malloc_handler(sizeof(t_node_exec));
    exec_node1->type = EXEC;
    exec_node1->name_exec = "sleep-command";
    exec_node1->file_path = "/bin/sleep";

    char *args1[] = {"/bin/sleep", "6", NULL};
    size_t argc1 = sizeof(args1) / sizeof(args1[0]);
    exec_node1->argv = malloc_handler(argc1 * sizeof(char*));
    for (size_t i = 0; i < argc1; i++) {
        exec_node1->argv[i] = args1[i];
    }

    char *env1[] = {"PATH=/bin", NULL};
    size_t envc1 = sizeof(env1) / sizeof(env1[0]);
    exec_node1->env = malloc_handler(envc1 * sizeof(char*));
    for (size_t i = 0; i < envc1; i++) {
        exec_node1->env[i] = env1[i];
    }

    // Initialisierung von exec_node2
    t_node_exec *exec_node2 = malloc_handler(sizeof(t_node_exec));
    exec_node2->type = EXEC;
    exec_node2->name_exec = "ls-command";
    exec_node2->file_path = "/bin/ls";

    char *args2[] = {"/bin/ls", "-l", NULL};
    size_t argc2 = sizeof(args2) / sizeof(args2[0]);
    exec_node2->argv = malloc_handler(argc2 * sizeof(char*));
    for (size_t i = 0; i < argc2; i++) {
        exec_node2->argv[i] = args2[i];
    }

    exec_node2->env = malloc_handler(envc1 * sizeof(char*));
    for (size_t i = 0; i < envc1; i++) {
        exec_node2->env[i] = env1[i];
    }

    // Initialisierung von exec_node3
    t_node_exec *exec_node3 = malloc_handler(sizeof(t_node_exec));
    exec_node3->type = EXEC;
    exec_node3->name_exec = "wc-command";
    exec_node3->file_path = "/bin/wc";

    char *args3[] = {"/bin/wc", "-l", NULL};
    size_t argc3 = sizeof(args3) / sizeof(args3[0]);
    exec_node3->argv = malloc_handler(argc3 * sizeof(char*));
    for (size_t i = 0; i < argc3; i++) {
        exec_node3->argv[i] = args3[i];
    }

    exec_node3->env = malloc_handler(envc1 * sizeof(char*));
    for (size_t i = 0; i < envc1; i++) {
        exec_node3->env[i] = env1[i];
    }

    // Initialisierung von pipe_node2
    t_node_pipe *pipe_node2 = malloc_handler(sizeof(t_node_pipe));
    pipe_node2->type = PIPE;
    pipe_node2->name_Pipe = "2. second Pipe";
    pipe_node2->left_node = malloc_handler(sizeof(t_node));
    pipe_node2->left_node->node_type = exec_node2;
    pipe_node2->left_node->type = EXEC;
    pipe_node2->right_node = malloc_handler(sizeof(t_node));
    pipe_node2->right_node->node_type = exec_node3;
    pipe_node2->right_node->type = EXEC;

    // Initialisierung von pipe_node1
    t_node_pipe *pipe_node1 = malloc_handler(sizeof(t_node_pipe));
    pipe_node1->type = PIPE;
    pipe_node1->name_Pipe = "1. first Pipe";
    pipe_node1->left_node = malloc_handler(sizeof(t_node));
    pipe_node1->left_node->node_type = exec_node1;
    pipe_node1->left_node->type = EXEC;
    pipe_node1->right_node = malloc_handler(sizeof(t_node));
    pipe_node1->right_node->node_type = pipe_node2;
    pipe_node1->right_node->type = PIPE;

    // Erstellen des Rückgabeknotens
    t_node *ret = malloc_handler(sizeof(t_node));
    ret->node_type = pipe_node1;
    ret->type = PIPE;

    return ret;
}




t_node *set_test_list_2(void) {
    // command `ls -l | wc -l`
    t_node_exec *exec_node2;
    t_node_exec *exec_node3;
    t_node_pipe *pipe_node1;
    t_node *ret;

    // Initialisierung von exec_node2
    exec_node2 = malloc_handler(sizeof(t_node_exec));
    exec_node2->type = EXEC;
    exec_node2->name_exec = "ls-command";
    exec_node2->file_path = "/bin/ls";

    // Dynamische Allokation und Initialisierung für argv von exec_node2
    char *args2[] = {"/bin/ls", "-l", NULL};
    size_t argc2 = sizeof(args2) / sizeof(args2[0]);
    exec_node2->argv = malloc_handler(argc2 * sizeof(char*));
    for (size_t i = 0; i < argc2; i++) {
        exec_node2->argv[i] = args2[i];
    }

    // Initialisierung von env für exec_node2 (wenn erforderlich)
    exec_node2->env = malloc_handler(1 * sizeof(char*));
    exec_node2->env[0] = NULL;

    // Initialisierung von exec_node3
    exec_node3 = malloc_handler(sizeof(t_node_exec));
    exec_node3->type = EXEC;
    exec_node3->name_exec = "wc-command";
    exec_node3->file_path = "/bin/wc";

    // Dynamische Allokation und Initialisierung für argv von exec_node3
    char *args3[] = {"/bin/wc", "-l", NULL};
    size_t argc3 = sizeof(args3) / sizeof(args3[0]);
    exec_node3->argv = malloc_handler(argc3 * sizeof(char*));
    for (size_t i = 0; i < argc3; i++) {
        exec_node3->argv[i] = args3[i];
    }

    // Dynamische Allokation und Initialisierung für env von exec_node3
    char *env3[] = {"PATH=/bin", NULL};
    size_t envc3 = sizeof(env3) / sizeof(env3[0]);
    exec_node3->env = malloc_handler(envc3 * sizeof(char*));
    for (size_t i = 0; i < envc3; i++) {
        exec_node3->env[i] = env3[i];
    }

    // Initialisierung von pipe_node1
    pipe_node1 = malloc_handler(sizeof(t_node_pipe));
    pipe_node1->type = PIPE;
    pipe_node1->name_Pipe = "1. first Pipe";
    pipe_node1->left_node = malloc_handler(sizeof(t_node));
    pipe_node1->left_node->node_type = exec_node2;
    pipe_node1->left_node->type = EXEC;
    pipe_node1->right_node = malloc_handler(sizeof(t_node));
    pipe_node1->right_node->node_type = exec_node3;
    pipe_node1->right_node->type = EXEC;

    // Erstellen des Rückgabeknotens
    ret = malloc_handler(sizeof(t_node));
    ret->node_type = pipe_node1;
    ret->type = PIPE;

    return ret;
}


t_node *set_test_list_3 (void)
{
	// command ` ls -l | wc -l
	t_node *ret;

	t_node_exec *exec = malloc_handler(sizeof(t_node_exec));
	exec->file_path = "/bin/ls";
	char *args[] = {"/bin/ls", "-l", NULL};
    size_t argc = sizeof(args) / sizeof(args[0]);

    exec->argv = malloc_handler(argc * sizeof(char*));
    for (size_t i = 0; i < argc; i++) {
        exec->argv[i] = args[i];
    }
	char *envp[] = {"PATH=/bin", NULL};
    size_t envc = sizeof(envp) / sizeof(envp[0]);

    exec->env = malloc_handler(envc * sizeof(char*));
    for (size_t i = 0; i < envc; i++) {
        exec->env[i] = envp[i];
    }

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = exec;
	ret->type = EXEC;
	return (ret);	
}

void print_test_list (t_list_dc *list)
{
	t_list_dc *list_cp;

	list_cp = list;
	while (list_cp != NULL)
	{
		printf("Path: %s\n", ((t_node_exec *)(list_cp->content))->file_path);
		list_cp = list_cp->next;
	}
}

void list_test_use(void)
{
	//int pipefd[2];
    pid_t pid;

	pid = fork_handler();
	if (pid == 0) // Kindprozess
    {
			navigate_tree_forward(set_test_list_2());
    }
    else
	{
		wait(NULL);
	}
	printf("Ausfürung beendet\n");
}