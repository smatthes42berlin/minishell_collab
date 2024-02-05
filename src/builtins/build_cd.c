#include "minishell.h"

// clear the string from "./" an dubbel /
static char *clear_str(char *path);
static char *set_env_cd (char *keyword);
static void execution_pipesetting(t_pipefd *pipefd, char **env);

// return alltime NULL
char *build_cd (t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char *env_new[3];

// Uselese maybe only for data if i am needet later ?
	if (data->ast == NULL)
		printf("NOTING CD DEBUGGER");
	
	env_new[0] = set_env_cd("OLDPWD=");
	printf("\nclearsting: %s ; %s\n", clear_str(node->argv[0]), node->argv[0]);
	if (chdir(clear_str(node->argv[0])) == -1)
		error_code_handler(errno, "ERR-chdir", "CD -Command --> ", node->argv[0]);
	env_new[1] = set_env_cd("PWD=");
	env_new[2] = NULL;
	execution_pipesetting(pipefd, env_new);
	// free env_new !!! 
	return (NULL);
}

static void execution_pipesetting(t_pipefd *pipefd, char **env)
{
	int i_count;
	i_count = 0; 
	close(pipefd->pipefd[0]);
	while (env[i_count] != NULL)
	{
		printf("New env - write : %s\n", env[i_count]);
        write(pipefd->pipefd[1], env[i_count], strlen(env[i_count]) + 1);
        i_count++;
    }
	close(pipefd->pipefd[1]);
}

static char *set_env_cd (char *keyword)
{
	char *path;
	char *str;
	
	path = build_pwd();
	str = ft_strjoin(keyword, path);
	free(path);
	return (str);
}

// clear the string from "./" an dubbel /
static char *clear_str(char *path)
{
	int i;
	char **str;
	char *ret;

	ret = "";
	i = -1;
	str = ft_split_str(path, "/");
	while (str[++i] != NULL)
	{
		if (ft_strncmp(str[i], ".", ft_strlen(".")) == 0 
			&& str[i][1] == '\0')
			;
		else
			ret = ft_strjoin(ft_strjoin(ret, str[i]), "/");
	}
	free_str_arr_null(str);
	return (ret);	
}

//-----------------------------------------Tests -----------------------

t_node	*set_cd_absolut(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_exec("test pwd", "cd", "/home/rkost/Project/Rank03/minishell_collab/src/execution", true);
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
	ret->node_type = test_cmd_exec("test pwd", "cd", ".././././../////trash", true);
	ret->type = EXEC;
	return (ret);
}
