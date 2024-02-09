
#include "minishell.h"

int	check_cmd_access(char **env_vars, char *cmd_arg, char **exec_path)
{
	int		i;
	char	**path;

	if (get_path(env_vars, &path))
		return (1);
	*exec_path = NULL;
	i = 0;
	if (access(cmd_arg, X_OK) == 0)
		return (ft_str_n_dup_int(cmd_arg, 0, exec_path));
	while (path[i])
	{
		if (!check_path_combination(path[i], cmd_arg, exec_path))
			break ;
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
		return (printf("Error joining path string"));
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
		return (printf("Error splitting path variable"));
	}
	return (0);
}
