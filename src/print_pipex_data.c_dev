/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pipex_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 07:52:16 by smatthes          #+#    #+#             */
/*   Updated: 2023/11/10 13:36:46 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_pipex_data(t_pipex_data *data)
{
	ft_printf_fd(2, "fd_pipe: $ %d $ $ %d $\n", data->fd_pipe[0],
			data->fd_pipe[1]);
	ft_printf_fd(2, "infile: $ %s $\n", data->infile);
	ft_printf_fd(2, "outfile: $ %s $\n", data->outfile);
	ft_printf_fd(2, "cmd 1 str: $ %s $\n", data->cmd_str_1);
	ft_printf_fd(2, "cmd 1 arr:\n");
	print_str_arr_null(data->cmd_arg_1);
	ft_printf_fd(2, "cmd 2 str: $ %s $\n", data->cmd_str_2);
	ft_printf_fd(2, "cmd 2 arr:\n");
	print_str_arr_null(data->cmd_arg_2);
	ft_printf_fd(2, "child 1 pid: $ %d $\n", data->child_1_pid);
	ft_printf_fd(2, "child 2 pid: $ %d $\n", data->child_2_pid);
	ft_printf_fd(2, "path arr:\n");
	print_str_arr_null(data->path);
	ft_printf_fd(2, "cmd 1 exec path: $ %s $\n", data->exec_path_1);
	ft_printf_fd(2, "cmd 2 exec path: $ %s $\n", data->exec_path_2);
}
