#include "minishell.h"

// clear the string from "./" an dubbel /
static	char	*ft_clear_str(char *path);
static	char	*creat_env_var(char *keyword, char *type, bool newline);
static	char	**wrong_path(int err, t_node_exec *node);
static	char	**path_exist(char *oldpwd, int err);

// return alltime NULL
char	**build_cd(t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char	**ret;
	char	*oldpwd;
	char	*str_tmp;
	int		i;

	oldpwd = creat_env_var("OLDPWD=", ADD_ENV, false);
	if (node->argv[1] == NULL)
		str_tmp = env_get_var(data, "HOME");
	else
		str_tmp = ft_clear_str(node->argv[1]);
	i = chdir(str_tmp);
	if (i == -1 || node->argv[2] != NULL)
		ret = wrong_path(i, node);
	else
		ret = path_exist(oldpwd, i);
	write_pipe_to_executor_pipe(pipefd->pipefd, ret, "function \"build_cd\"");
	free_str_arr_null(ret);
	return (NULL);
}

static char	*creat_env_var(char *keyword, char *type, bool newline)
{
	char	*str_tmp;
	char	**ret;
	char	*char_ret;
	char	*err_msg;

	err_msg = "function \"creat_env_var\" for build cd";
	ret = build_pwd(newline);
	str_tmp = use_strjoin(keyword, ret[0], err_msg);
	free(ret[0]);
	free(ret[1]);
	char_ret = use_strjoin(type, str_tmp, err_msg);
	free(str_tmp);
	return (char_ret);
}

// clear the string from "./" an double /
static char	*ft_clear_str(char *path)
{
	int		i;
	char	**str;
	char	*ret;
	char	*str_tmp;
	char	*err_msg;

	err_msg = "function \"ft_clear_str\" for build cd";
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
			str_tmp = use_strjoin(ret, str[i], err_msg);
			free(ret);
			ret = use_strjoin(str_tmp, "/", err_msg);
			free(str_tmp);
		}
	}
	free_str_arr_null(str);
	return (ret);
}

static	char	**wrong_path(int err, t_node_exec *node)
{
	char	**ret;
	char	*err_msg;

	err_msg = "function wrong_path";
	ret = use_malloc(sizeof(char *) * 2, err_msg);
	if (err == -1)
		ret[0] = use_strjoin(EXIT_CODE,
				"exit=1_MSG=minishell: No such file or directory",
				err_msg);
	else if (node->argv[2] != NULL)
		ret[0] = use_strjoin(EXIT_CODE,
				"exit=1_MSG=minishell: cd: too many arguments",
				err_msg);
	ret[1] = NULL;
	return (ret);
}

static	char	**path_exist(char *oldpwd, int err)
{
	char	**ret;
	char	*err_msg;

	err_msg = "function path_exit";
	ret = use_malloc(sizeof(char *) * 5, err_msg);
	ret[0] = ft_strdup(oldpwd);
	ret[1] = creat_env_var("PWD=", ADD_ENV, false);
	ret[2] = creat_env_var("PWD=", ADD_CD, false);
	if (err == -1)
		ret[3] = use_strjoin(EXIT_CODE, "exit=1", err_msg);
	else
		ret[3] = use_strjoin(EXIT_CODE, "exit=0", err_msg);
	ret[4] = NULL;
	return (ret);
}
