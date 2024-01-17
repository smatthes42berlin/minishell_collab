/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:38:37 by rene              #+#    #+#             */
/*   Updated: 2024/01/17 11:50:48 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pipe_handler(int *pipefd)
{
    if (pipe(pipefd) < 0)
        error_code_handler(errno, "ERR-pipe", " ", " ");
}

void pipe_setting(int *pipefd, bool open)
{
	if (open)
	{
		close(pipefd[0]);
		dup2(pipfd[1], STDOUT_FILENO);
		close(pipfd[1]);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipfd[0], STDIN_FILENO);
		close(pipfd[0]);
	}	
}