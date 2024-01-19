/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:49:43 by rkost             #+#    #+#             */
/*   Updated: 2024/01/19 09:07:14 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_main_data_test(t_main_data *main_data)
{
	main_data->ast->content = NULL;
	main_data->cli_input = NULL;
	main_data->env_vars = NULL;
	main_data->token_list = NULL;
}

void	test_exece(void)
{
	t_node_exec exec;
	exec.file_path = "/bin/cat";
	exec.argv = (char *[]){"/bin/cat", "input", "input2",  NULL}; 
	exec.env = (char *[]){"PATH=/bin", NULL};
	execve_handler(&exec);
}

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

t_list_dc *set_test_list (void)
{
	// command `sleep 2 | ls -l | wc -l
	t_node_exec *exec_node1;
	t_node_exec *exec_node2;
	t_node_exec *exec_node3;
	t_list_dc *list; 
	
	exec_node1 = malloc(sizeof(t_node_exec));
    exec_node1->type = EXEC; 
    exec_node1->file_path = "/bin/sleep";
    exec_node1->argv = (char *[]){"/bin/sleep", "5", NULL}; 
    exec_node1->env = (char *[]){"PATH=/bin", NULL};

	exec_node2 = malloc(sizeof(t_node_exec));
    exec_node2->type = EXEC; 
    exec_node2->file_path = "/bin/ls";
    exec_node2->argv = (char *[]){"/bin/ls", "-l", NULL};
    exec_node2->env = (char *[]){"PATH=/bin", NULL};

	exec_node3 = malloc(sizeof(t_node_exec));
    exec_node3->type = EXEC; 
    exec_node3->file_path = "/bin/wc";
    exec_node3->argv = (char *[]){"/bin/wc", "-l", NULL}; 
    exec_node3->env = (char *[]){"PATH=/bin", NULL};
	
	
	list = malloc(sizeof(t_list_dc));
	list->prev = NULL;
	list->content = exec_node1;
	list->next = malloc(sizeof(t_list_dc));
	list->next->prev = list;
	list->next->content = exec_node2;
	list->next->next = malloc(sizeof(t_list_dc));
	list->next->next->prev = list->next;
	list->next->next->content = exec_node3;
	list->next->next->next = NULL;

	return (list);	
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
	print_test_list(set_test_list());
}