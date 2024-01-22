/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:04:34 by rkost             #+#    #+#             */
/*   Updated: 2024/01/22 18:43:32 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief using the execve function
 *
 * @param exec struct for execve
 */
void	execve_handler(t_node_exec *exec)
{
	if (access_handler(exec->file_path, FILE_EXISTS) == 0)
	{
		if (execve(exec->file_path, exec->argv, exec->env) == -1)
		{
			error_code_handler(errno, "ERR-execve", exec->file_path, " ");
			exit(EXIT_FAILURE);
		}
	}
	else
		printf("ERR-execve: (access-Error) No executable file path"
			"please check the path!");
}