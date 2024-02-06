#include "minishell.h"

// clear the string from "./" an dubbel /
static char *ft_clear_str(char *path);
static char *read_pwd (char *keyword);
static void pipesetting_for_env(t_pipefd *pipefd, char **env);

// return alltime NULL
char *build_cd (t_node_exec *node, t_pipefd *pipefd)
{
	char *env_new[3];
	char *clear_str;

	env_new[0] = read_pwd("OLDPWD=");
	clear_str = ft_clear_str(node->argv[0]);
	if (chdir(clear_str) == -1)
		error_code_handler(errno, "ERR-chdir", "CD -Command --> ", node->argv[0]);
	env_new[1] = read_pwd("PWD=");
	env_new[2] = NULL;
	pipesetting_for_env(pipefd, env_new);
	free(env_new[0]);
	free(env_new[1]);
	free(env_new[2]);
	
	//free_str_arr_null(env_new);
	free(clear_str);
	return (NULL);
}

static void pipesetting_for_env(t_pipefd *pipefd, char **env)
{
	int i_count;
	i_count = 0; 
	close(pipefd->pipefd[0]);
	while (env[i_count] != NULL)
	{
        write(pipefd->pipefd[1], env[i_count], strlen(env[i_count]) + 1);
        i_count++;
    }
	close(pipefd->pipefd[1]);
}

static char *read_pwd (char *keyword)
{
	char *str_tmp;
	char *ret;
	
	ret = build_pwd();
	str_tmp = ft_strjoin(keyword, ret);
	free(ret);
	ret = ft_strjoin(ADD_ENV, str_tmp);
	free(str_tmp);
	return (ret);
}

// clear the string from "./" an dubbel /
static char *ft_clear_str(char *path)
{
	int i;
	char **str;
	char *ret;
	char *str_tmp;

	ret = malloc_handler(sizeof(char));
	ret[0] = '\0'; 
	i = -1;
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

//-----------------------------------------Tests -----------------------

t_node	*set_cd_absolut(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_exec("test cd", "cd", "/home/rkost/Project/Rank03/minishell_collab/src/execution", true);
	ret->type = EXEC;
	return (ret);
}

t_node	*set_cd_relativ(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_exec("test cd", "cd", "src/execution", true);
	ret->type = EXEC;
	return (ret);
}

t_node	*set_cd_relativ_revers(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_exec("test cd", "cd", ".././././../////trash", true);
	ret->type = EXEC;
	return (ret);
}
