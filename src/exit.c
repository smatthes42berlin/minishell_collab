/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 07:52:16 by smatthes          #+#    #+#             */
/*   Updated: 2023/11/18 14:17:19 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_exit_error(t_pipex_data *data, int code, char *message)
{
	perror(message);
	free_args_handling(data);
	exit(code);
}

void	clean_exit_main(t_pipex_data *data, int code)
{
	free_args_handling(data);
	exit(code);
}

void	clean_exit_127(t_pipex_data *data, char *cmd)
{
	ft_printf_fd(2, "%s: command not found\n", cmd);
	free_args_handling(data);
	exit(127);
}
