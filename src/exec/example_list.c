/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:49:43 by rkost             #+#    #+#             */
/*   Updated: 2024/01/15 17:45:12 by rkost            ###   ########.fr       */
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
	exec.argv = (char *[]){"ls", "-l", NULL}; 
	exec.env = (char *[]){"PATH=/bin", NULL};
	safe_execve_handler(&exec);
}