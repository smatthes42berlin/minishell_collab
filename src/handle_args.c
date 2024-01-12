/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 07:52:16 by smatthes          #+#    #+#             */
/*   Updated: 2023/11/12 16:10:28 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_args(t_pipex_data *data, int argc, char *argv[], char *envp[])
{
	if (argc != 5)
		return (-1);
	data->infile = argv[1];
	data->cmd_str_1 = argv[2];
	data->cmd_str_2 = argv[3];
	data->outfile = argv[4];
	data->envp = envp;
	if (split_cmd_args(data->cmd_str_1, &(data->cmd_arg_1)) == -1)
		return (free_args_handling_status(data, 0));
	if (split_cmd_args(data->cmd_str_2, &(data->cmd_arg_2)) == -1)
		return (free_args_handling_status(data, 1));
	if (get_path(data->envp, &(data->path)) == -1)
		return (free_args_handling_status(data, 2));
	if (check_cmd_access(data, data->cmd_arg_1, &(data->exec_path_1)) == -1)
		return (free_args_handling_status(data, 3));
	if (check_cmd_access(data, data->cmd_arg_2, &(data->exec_path_2)) == -1)
		return (free_args_handling_status(data, 3));
	return (1);
}

int	free_args_handling_status(t_pipex_data *data, int status)
{
	if (status == 1)
		free_cmd_arg1(data);
	if (status == 2)
		free_cmd_arg1_2(data);
	if (status == 3)
		free_cmd_arg1_2_path(data);
	return (-1);
}
