/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:22:41 by rkost             #+#    #+#             */
/*   Updated: 2024/01/22 22:09:17 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_node *node);

t_node	*example_selection(void)
{
	t_node	*ret;

	// ret = set_cmd_1();
	// ret = set_cmd_2();
	ret = set_cmd_3();
	// ret = set_cmd_4();
	// ret = set_redir_in_1();
	// ret = set_redir_in_1_cmd_2();
	// ret = set_redir_out_1();
	return (ret);
}

void	executor(void)
{
	pid_t	pid;
	t_list	*pid_list;
	t_node	*example;

	{
		pid = fork_handler();
		if (pid == 0)
		{
			pid_list = NULL;
			example = set_cmd_3(); // Wenn der Phrase im Kindprozess steht ist der Memory frei! und es gibt keine mem-leaks! 
			navigate_tree_forward(example, &pid_list);
			print_list_pid_list(pid_list);
			wait_for_all_processes(pid_list);
			free_list_pid_list(pid_list);
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
}

// void	free_string_array(char **array)
// {
// 	if (array == NULL)
// 		return ;
// 	for (int i = 0; array[i] != NULL; i++)
// 		free(array[i]);
// 	free(array);
// }

// void	free_tree(t_node *node)
// {
// 	if (node == NULL)
// 		return ;

// 	if (node->type == EXEC)
// 	{
// 		t_node_exec *exec_node = (t_node_exec *)node->node_type;
// 		// Freigabe von argv und env
// 		free_string_array(exec_node->argv);
// 		free_string_array(exec_node->env);
// 		free(exec_node);
// 	}
// 	else if (node->type == PIPE)
// 	{
// 		t_node_pipe *pipe_node = (t_node_pipe *)node->node_type;
// 		// Rekursive Freigabe der Kindknoten
// 		free_tree(pipe_node->left_node);
// 		free_tree(pipe_node->right_node);
// 		free(pipe_node);
// 	}
// 	else if (node->type == REDIR)
// 	{
// 		t_node_redir *redir_node = (t_node_redir *)node->node_type;
// 		// Rekursive Freigabe des Kindknotens
// 		free_tree(redir_node->child_node);
// 		free(redir_node);
// 	}
// 	free(node);
// }