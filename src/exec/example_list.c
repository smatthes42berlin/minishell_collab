/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:49:43 by rkost             #+#    #+#             */
/*   Updated: 2024/01/16 19:04:00 by rkost            ###   ########.fr       */
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
	exec.file_path = "/bin/ls";
	exec.argv = (char *[]){"/bin/ls", "-l", NULL}; 
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
        buffer[bytesRead] = '\0'; // Setze das Ende des Strings
        printf("%s", buffer);
    }

    if (bytesRead == -1) {
        perror("Fehler beim Lesen der Datei");
        close(fd);
        return ;
    }

	close_handler(fd);	
}

/**
 * @brief Fork Handling 
 * --> pid_t list --> 
 * 
 */