#include "minishell.h"

// clear the string from "./" an dubbel /
static char	*ft_clear_str(char *path);
static char	*creat_env_var(char *keyword, char *type, bool newline);
static char	*absoult_or_relativ_path(char *path);

// return alltime NULL
char	**build_cd(t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char	*env_new[4];
	char	*str_tmp;
	int		i;

	if (data->ast->type == PIPE)
		return (NULL);
	env_new[0] = creat_env_var("OLDPWD=", ADD_ENV, true);
	if (node->argv[1] == NULL)
		str_tmp = env_get_var(data, "HOME");
	else
		str_tmp = ft_clear_str(node->argv[1]);
	i = chdir(str_tmp);
	if (i == -1)
		error_code_handler(errno, 
		"ERR-chdir", "CD -Command cd-buid funktion --> ", str_tmp);
	env_new[1] = creat_env_var("PWD=", ADD_ENV, true);
	env_new[2] = creat_env_var("PWD=", ADD_CD, false);
	env_new[3] = NULL;
	pipe_setting(pipefd->pipefd, true, env_new);
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
	char	*ret;

	ret = NULL;
	if (path[0] == '/')
	{
		ret = malloc_handler(sizeof(char) * 2);
		ret[0] = '/';
		ret[1] = '\0';
	}
	else
	{
		ret = malloc_handler(sizeof(char));
		ret[0] = '\0';
	}
	return (ret);
}