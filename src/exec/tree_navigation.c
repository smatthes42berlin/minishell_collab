/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_navigation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:25:45 by rkost             #+#    #+#             */
/*   Updated: 2024/01/22 23:11:52 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redim_exec_check(t_node *node, t_list *pid_list);
void	nested_fork_parent(t_node *left, t_node *right, t_list *pid_list);

void	navigate_tree_forward(t_node *node, t_list **pid_list)
{
	if (node == NULL)
		error_code_handler(1000, "ERR-tree-navigation no node", "", "");
	if (node->type == PIPE)
	{
		type_pipe(node, pid_list);
	}
	else
		redim_exec_check(node, *pid_list);
}
