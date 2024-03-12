#include "minishell.h"

// clear the string from "./" an dubbel /
//static	char	*ft_clear_str(char *path);
static	char	*creat_env_var(char *keyword, char *type);
static	char	**wrong_path(int err, t_node_exec *node, t_pipefd *pipefd);
static	char	**path_exist(char *oldpwd, int err, t_pipefd *pipefd);

// return alltime NULL
char	**build_cd(t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char	**ret;
	char	*oldpwd;
	char	*str_tmp;
	int		i;

	oldpwd = creat_env_var("OLDPWD=", ADD_ENV);
	str_tmp = check_cd_argument(data, node);
	i = chdir(str_tmp);
	if (i == -1)
		ret = wrong_path(i, node, pipefd);
	else if (node->argv[1] == NULL)
		ret = path_exist(oldpwd, i, pipefd);
	else if (node->argv[2] != NULL)
		ret = wrong_path(i, node, pipefd);
	else
		ret = path_exist(oldpwd, i, pipefd);
	free(oldpwd);
	free(str_tmp);
	write_pipe_to_executor_pipe(pipefd->pipefd, ret, "function \"build_cd\"");
	free_str_arr_null(ret);
	return (NULL);
}

static char	*creat_env_var(char *keyword, char *type)
{
	char	*str_tmp;
	char	*ret;
	char	*err_msg;

	err_msg = "function \"creat_env_var\" for build cd";
	ret = use_getcwd(err_msg);
	str_tmp = use_strjoin(keyword, ret, err_msg);
	free(ret);
	ret = use_strjoin(type, str_tmp, err_msg);
	free(str_tmp);
	return (ret);
}

static char	*chreat_err_msg(char *err_msg, char *path)
{
	char	*str_ret;
	char	*str_tmp;

	str_ret = use_strjoin(EXIT_CODE, "_MSG=minishell: cd: ", err_msg);
	str_tmp = use_strjoin(str_ret, path, err_msg);
	free(str_ret);
	str_ret = use_strjoin(str_tmp, ": No such file or directory", err_msg);
	free(str_tmp);
	return (str_ret);
}

static	char	**wrong_path(int err, t_node_exec *node, t_pipefd *pipefd)
{
	char	**ret;
	char	*err_msg;

	err_msg = "function wrong_path -> build_cd";
	ret = use_malloc(sizeof(char *) * 2, err_msg);
	ret[0] = NULL;
	if (node->argv[1][0] == '.' && node->argv[1][1] == '\0')
		pipefd->exit_code_buildin = 0;
	else if (err == -1 && node->argv[2] == NULL)
	{
		pipefd->exit_code_buildin = 1;
		ret[0] = chreat_err_msg(err_msg, node->argv[1]);
	}
	else if (node->argv[2] != NULL)
	{
		pipefd->exit_code_buildin = 1;
		ret[0] = use_strjoin(EXIT_CODE,
				"_MSG=minishell: cd: too many arguments", err_msg);
	}
	else
		pipefd->exit_code_buildin = 0;
	ret[1] = NULL;
	return (ret);
}

static	char	**path_exist(char *oldpwd, int err, t_pipefd *pipefd)
{
	char	**ret;
	char	*err_msg;

	err_msg = "function path_exit";
	ret = use_malloc(sizeof(char *) * 4, err_msg);
	ret[0] = ft_strdup(oldpwd);
	ret[1] = creat_env_var("PWD=", ADD_ENV);
	ret[2] = creat_env_var("PWD=", ADD_CD);
	if (err == -1)
		pipefd->exit_code_buildin = 1;
	else
		pipefd->exit_code_buildin = 0;
	ret[3] = NULL;
	return (ret);
}
