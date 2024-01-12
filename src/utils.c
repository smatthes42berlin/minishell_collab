/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 07:52:16 by smatthes          #+#    #+#             */
/*   Updated: 2023/11/18 14:19:03 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	split_cmd_args(char *cmd_args_str, char ***cmd_args_arr)
{
	*cmd_args_arr = ft_split_single_quotes(cmd_args_str, ' ');
	if (!(*cmd_args_arr))
		return (-1);
	return (1);
}

int	get_path(char *envp[], char ***path)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return (-1);
	*path = ft_split((envp[i] + 5), ':');
	if (!(*path))
	{
		free_str_arr_null(*path);
		return (-1);
	}
	return (1);
}

int	check_cmd_access(t_pipex_data *data, char **cmd_arg, char **exec_path)
{
	int		i;
	char	*path;
	int		status;

	*exec_path = NULL;
	i = 0;
	if (access(cmd_arg[0], X_OK) == 0)
	{
		status = ft_str_n_dup_int(cmd_arg[0], 0, exec_path);
		return (status);
	}
	while (data->path[i])
	{
		status = ft_join_n_str(&path, 3, data->path[i], "/", cmd_arg[0]);
		if (status == -1)
			return (-1);
		if (access(path, X_OK) == 0)
		{
			*exec_path = path;
			break ;
		}
		free(path);
		i++;
	}
	return (1);
}
