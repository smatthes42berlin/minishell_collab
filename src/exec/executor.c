/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execuater.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:22:41 by rkost             #+#    #+#             */
/*   Updated: 2024/01/22 18:31:06 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_test_use(void)
{
	pid_t pid;
	pid = fork_handler();
	if (pid == 0)
	{
		t_list *pid_list;

		pid_list = NULL;
		t_node *example;
		t_node *head_example;
		example = set_redir_in_1_cmd_2();
		head_example = example;
		print_type(example);
		navigate_tree_forward(example, &pid_list);
		print_type(head_example);
		navigate_tree_forward(head_example, &pid_list);
		wait_for_all_processes(pid_list);
		print_list_pid_list(pid_list);
		free_list_pid_list(pid_list);
		printf("Ausfürung beendet---\n");
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}