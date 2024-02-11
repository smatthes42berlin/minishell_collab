#include "minishell.h"

// clear the string from "./" an dubbel /
static char *ft_clear_str(char *path);
static char *creat_env_var(char *keyword, char *type, bool newline);
static char *absoult_or_relativ_path(char *path);

// return alltime NULL
char **build_cd (t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char *env_new[4];
	char *str_tmp;
	int i;

	if (data->ast->type == PIPE)
	{
		return (NULL);
	}
	env_new[0] = creat_env_var("OLDPWD=", ADD_ENV, true);
	if (node->argv[1] == NULL)
	{
		str_tmp = env_get_var(data, "HOME");
		i = chdir(str_tmp);
	}
	else
	{
		str_tmp = ft_clear_str(node->argv[1]);
		i = chdir(str_tmp);
	}
	if (i == -1)
		error_code_handler(errno, "ERR-chdir", "CD -Command cd -buid funktion --> ", str_tmp);
	env_new[1] = creat_env_var("PWD=", ADD_ENV, true);
	env_new[2] = creat_env_var("PWD=", ADD_CD, false);
	env_new[3] = NULL;	
	pipe_setting(pipefd->pipefd, true ,env_new);
	// i = 0;	
	// while (0 < 4)
	// free(env_new[i]);
	// free(str_tmp);
	return (NULL);
}

static char *creat_env_var(char *keyword, char *type, bool newline)
{
	char *str_tmp;
	char **ret;
	char *char_ret;
	
	ret = build_pwd(newline);
	str_tmp = ft_strjoin(keyword, ret[0]);
	free(ret[0]);
	free(ret[1]);
	char_ret = ft_strjoin(type, str_tmp);
	free(str_tmp);
	return (char_ret);
}

// clear the string from "./" an dubbel /
static char *ft_clear_str(char *path)
{
	int i;
	char **str;
	char *ret;
	char *str_tmp;

	print_debugging_info_executer(INT_DEBUG, 25, NULL);
	i = -1;
	ret = absoult_or_relativ_path(path);
	str = ft_split_str(path, "/");
	while (str[++i] != NULL)
	{
		if (ft_strncmp(str[i], ".", ft_strlen(".")) == 0 
			&& str[i][1] == '\0')
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

static char *absoult_or_relativ_path(char *path)
{
	char *ret;

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
	return(ret); 
}
//-----------------------------------------Tests -----------------------

// t_node	*set_cd_absolut(void)
// {
// 	t_node	*ret;

// 	ret = malloc_handler(sizeof(t_node));
// 	ret->node_type = test_cmd_exec("test cd", "cd", "/home/rkost/Project/Rank03/minishell_collab/src/execution", true);
// 	ret->type = EXEC;
// 	return (ret);
// }

// t_node	*set_cd_relativ(void)
// {
// 	t_node	*ret;

// 	ret = malloc_handler(sizeof(t_node));
// 	ret->node_type = test_cmd_exec("test cd", "cd", "src/execution", true);
// 	ret->type = EXEC;
// 	return (ret);
// }

// t_node	*set_cd_relativ_revers(void)
// {
// 	t_node	*ret;

// 	ret = malloc_handler(sizeof(t_node));
// 	ret->node_type = test_cmd_exec("test cd", "cd", ".././././../////trash", true);
// 	ret->type = EXEC;
// 	return (ret);
// }

// t_node	*set_cd_redir_out(void)
// {
// 	t_node	*ret;

// 	ret = malloc_handler(sizeof(t_node));
// 	ret->node_type = test_cmd_redir("redir", "out", FILE_ONLY_WRITE, STDOUT, EXEC, 
// 		test_cmd_exec("test cd", "cd", "src/execution", true));
// 	ret->type = REDIR;
// 	return (ret);
// }

// t_node	*set_cd_cmd_2(void)
// {
// 	t_node	*ret;

// 	ret = malloc_handler(sizeof(t_node));
// 	ret->node_type = test_cmd_pipe("PIPE 1", EXEC, PIPE,
// 		test_cmd_exec("EXEC 1", "cd", "src/execution", true),
// 		test_cmd_pipe("PIPE 2", EXEC, EXEC, 
// 			test_cmd_exec("EXEC 2", "/bin/ls", "-l", false),
// 			test_cmd_exec("EXEC 3", "/bin/wc", "-l", false)));
// 	ret->type = PIPE;
// 	return (ret);

// }
