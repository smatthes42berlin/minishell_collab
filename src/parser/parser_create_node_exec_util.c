#include "minishell.h"

int	check_cmd_access(char **env_vars, char *cmd_arg, char **exec_path)
{
	char	**path;

	if (get_path(env_vars, &path))
		return (1);
	*exec_path = NULL;
	if (access(cmd_arg, X_OK) == 0)
	{
		free_str_arr_null(path);
		if (ft_str_n_dup_int(cmd_arg, 0, exec_path) == -1)
		{
			return (throw_error_custom((t_error_ms){errno, EPART_PARSER,
					EFUNC_MALLOC, "exec node copying path string"}));
		}
		return (0);
	}
	if (!path)
		return (0);
	if (check_all_comb(cmd_arg, exec_path, path))
		return (1);
	free_str_arr_null(path);
	return (0);
}

int	check_all_comb(char *cmd_arg, char **exec_path, char **path)
{
	int	i;
	int	comb_check;

	i = 0;
	while (path[i])
	{
		comb_check = check_path_combination(path[i], cmd_arg, exec_path);
		if (!comb_check)
			break ;
		if (comb_check > 0)
		{
			free_str_arr_null(path);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_path_combination(char *cur_path_val, char *cmd_arg, char **exec_path)
{
	int		status;
	char	*full_path;

	status = ft_join_n_str(&full_path, 3, cur_path_val, "/", cmd_arg);
	if (status == -1)
		return (throw_error_custom((t_error_ms){errno, EPART_PARSER,
				EFUNC_MALLOC, "exec node joining path string"}));
	if (access(full_path, X_OK) == 0)
	{
		*exec_path = full_path;
		return (0);
	}
	free(full_path);
	return (-1);
}

int	get_path(char *envp[], char ***path)
{
	int	i;

	i = 0;
	*path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return (0);
	*path = ft_split((envp[i] + 5), ':');
	if (!(*path))
	{
		return (throw_error_custom((t_error_ms){errno, EPART_PARSER,
				EFUNC_MALLOC, "exec node splitting path variable"}));
	}
	return (0);
}
