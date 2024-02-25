#include "minishell.h"

// clear the string from "./" an dubbel /
static char	*ft_clear_str(char *path);
static char	*creat_env_var(char *keyword, char *type, bool newline);
static char	*absoult_or_relativ_path(char *path);

// return alltime NULL
char	**build_cd(t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char	*ret[5];
	char	*str_tmp;
	int		i;

	ret[0] = creat_env_var("OLDPWD=", ADD_ENV, false);
	if (node->argv[1] == NULL)
		str_tmp = env_get_var(data, "HOME");
	else
		str_tmp = ft_clear_str(node->argv[1]);
	i = chdir(str_tmp);
	if (i == -1 || node->argv[2] != NULL)
	{
		free(ret[0]);
		if (i == -1)
			ret[0] = ft_strjoin(EXIT_CODE, "exit=1_MSG=minishell: No such file or directory");
		else if (node->argv[2] != NULL)
			ret[0] = ft_strjoin(EXIT_CODE, "exit=1_MSG=minishell: cd: too many arguments");
		ret[1] = NULL;
	}
	else
	{
		ret[1] = creat_env_var("PWD=", ADD_ENV, false);
		ret[2] = creat_env_var("PWD=", ADD_CD, false);
		if (i == -1)
			ret[3] = ft_strjoin(EXIT_CODE, "exit=1");
		else
			ret[3] = ft_strjoin(EXIT_CODE, "exit=0");
		ret[4] = NULL;
	}
	write_pipe_to_executor_pipe(pipefd->pipefd, ret, "function \"build_cd\"");
	// pipe_setting(pipefd->pipefd, true, ret, "function \"build_cd\"");
	return (NULL);
}

static char	*creat_env_var(char *keyword, char *type, bool newline)
{
	char	*str_tmp;
	char	**ret;
	char	*char_ret;

	ret = build_pwd(newline);
	str_tmp = ft_strjoin(keyword, ret[0]);
	free(ret[0]);
	free(ret[1]);
	char_ret = ft_strjoin(type, str_tmp);
	free(str_tmp);
	return (char_ret);
}

// clear the string from "./" an dubbel /
static char	*ft_clear_str(char *path)
{
	int		i;
	char	**str;
	char	*ret;
	char	*str_tmp;

	print_debugging_info_executer(INT_DEBUG, 25, NULL);
	i = -1;
	ret = absoult_or_relativ_path(path);
	str = ft_split_str(path, "/");
	while (str[++i] != NULL)
	{
		if (ft_strncmp(str[i], ".", ft_strlen(".")) == 0 && str[i][1] == '\0')
			;
		else
		{
			str_tmp = ft_strjoin(ret, str[i]);
			free(ret);
			ret = ft_strjoin(str_tmp, "/");
			free(str_tmp);
		}
	}
	free_str_arr_null(str);
	return (ret);
}

static char	*absoult_or_relativ_path(char *path)
{
	char *ret;

	ret = NULL;
	if (path[0] == '/')
	{
		ret = malloc(sizeof(char) * 2);
		if (!ret)
			throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
				"function \"absoult_or_relativ_path\" for \'cd\' command!"});
		ret[0] = '/';
		ret[1] = '\0';
	}
	else
	{
		ret = malloc(sizeof(char));
		if (!ret)
			throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
				"function \"absoult_or_relativ_path\" for \'cd\' command!"});
		ret[0] = '\0';
	}
	return (ret);
}