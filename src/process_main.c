/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 07:52:16 by smatthes          #+#    #+#             */
/*   Updated: 2023/11/12 16:58:29 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_main(t_pipex_data *data)
{
	int	status_1;
	int	res_wait_1;
	int	status_2;
	int	res_wait_2;

	if (close(data->fd_pipe[0]) == -1 || close(data->fd_pipe[1]) == -1)
		clean_exit_error(data, 1, "");
	res_wait_1 = waitpid(data->child_1_pid, &status_1, 0);
	res_wait_2 = waitpid(data->child_2_pid, &status_2, 0);
	if (res_wait_1 == -1 || res_wait_2 == -1)
		clean_exit_error(data, 1, "");
	if (WIFEXITED(status_2))
		res_wait_2 = WEXITSTATUS(status_2);
	if (WIFSIGNALED(status_2))
		res_wait_2 = WTERMSIG(status_2);
	clean_exit_main(data, res_wait_2);
}
