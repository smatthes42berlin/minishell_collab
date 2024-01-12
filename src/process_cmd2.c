/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 07:52:16 by smatthes          #+#    #+#             */
/*   Updated: 2023/11/18 16:23:23 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_cmd2(t_pipex_data *data)
{
	int	fd_out;

	if (close(data->fd_pipe[1]) == -1)
		clean_exit_error(data, 1, "");
	fd_out = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd_out == -1)
		clean_exit_error(data, 1, data->outfile);
	if (dup2(data->fd_pipe[0], STDIN_FILENO) == -1)
		clean_exit_error(data, 1, "");
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		clean_exit_error(data, 1, "");
	if (!data->exec_path_2)
		clean_exit_127(data, data->cmd_arg_2[0]);
	else
	{
		execve(data->exec_path_2, data->cmd_arg_2, data->envp);
		clean_exit_error(data, 1, "");
	}
}
