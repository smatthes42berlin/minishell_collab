/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 07:52:16 by smatthes          #+#    #+#             */
/*   Updated: 2023/11/18 15:53:05 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_cmd1(t_pipex_data *data)
{
	int	fd_in;

	if (close(data->fd_pipe[0]) == -1)
		clean_exit_error(data, 1, "");
	fd_in = open(data->infile, O_RDONLY);
	if (fd_in == -1)
		clean_exit_error(data, 1, ft_strjoin("bash: ", data->infile));
	if (dup2(fd_in, STDIN_FILENO) == -1)
		clean_exit_error(data, 1, "");
	if (dup2(data->fd_pipe[1], STDOUT_FILENO) == -1)
		clean_exit_error(data, 1, "");
	if (!data->exec_path_1)
		clean_exit_127(data, data->cmd_arg_1[0]);
	else
	{
		execve(data->exec_path_1, data->cmd_arg_1, data->envp);
		clean_exit_error(data, 1, "");
	}
}
