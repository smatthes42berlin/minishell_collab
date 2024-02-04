#include "minishell.h"

// clear the string from "./" an dubbel /
static char *clear_str(char *path);
static void set_env_cd (t_main_data *data, char *keyword);

// return alltime NULL
char *buid_cd (t_main_data *data, t_node_exec *node)
{
	set_env_cd(data, "OLDPWD=");
	printf("\nclearsting: %s ; %s\n", clear_str(node->argv[0]), node->argv[0]);
	if (chdir(clear_str(node->argv[0])) == -1)
		error_code_handler(errno, "ERR-chdir", "CD -Command --> ", node->argv[0]);
	set_env_cd(data, "PWD=");
	printf("%s\n", getcwd(NULL,0));
	return (NULL);
}

static void set_env_cd (t_main_data *data, char *keyword)
{
	char *path;
	char *str;
	

	path = build_pwd();
	str = ft_strjoin(keyword, path);
	printf("\n\n Changing from %s\n\n", str );
	env_set_var(data, str);
	free(str);
	free(path);
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
	ret->node_type = test_cmd_exec("test pwd", "cd", "/home/rkost/Project/Rank03/minishell_collab/src", true);
	ret->type = EXEC;
	return (ret);
}

t_node	*set_cd_relativ(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = test_cmd_exec("test cd", "cd", "src", true);
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
