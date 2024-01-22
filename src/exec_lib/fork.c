/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:25:27 by rene              #+#    #+#             */
/*   Updated: 2024/01/22 18:48:42 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief fork a Process and check for Error if fork failed
 *
 * @return pid_t
 */
pid_t	fork_handler(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_code_handler(errno, "ERR-fork", " ", " ");
	return (pid);
}

/**
 * @brief reading the Process status from a given Process ID
 *
 * @param pid Process ID to Check
 * @param block block it wait for end of the Child from the given Process ID
 * @return enum e_pid_satus
 */
enum e_pid_satus	process_status(pid_t pid, bool block)
{
	int		satus;
	pid_t	result;

	if (block)
		result = (waitpid(pid, &satus, 0));
	else
		result = (waitpid(pid, &satus, WNOHANG));
	if (result < 0)
	{
		error_code_handler(errno, "ERR-waitpid", " ", " ");
		return (PID_ERROR);
	}
	if (WIFEXITED(satus))
		return (PID_STOP_REGULAR);
	if (WIFSIGNALED(satus))
		return (PID_STOP_SIGNAL);
	if (WIFSTOPPED(satus))
		return (PID_BREAK);
	return (PID_RUNNING);
}