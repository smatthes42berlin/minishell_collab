/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:04:34 by rkost             #+#    #+#             */
/*   Updated: 2024/01/22 19:56:25 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief using the execve function
 *
 * @param exec struct for execve
 */
void	execve_handler(const char *file_path, char **argv, char **env)
{
	if (access_handler(file_path, FILE_EXISTS) == 0)
	{
		if (execve(file_path, argv, env) == -1)
		{
			error_code_handler(errno, "ERR-execve", file_path, " ");
			exit(EXIT_FAILURE);
		}
	}
	else
		printf("ERR-execve: (access-Error) No executable file path"
			"please check the path!");
}