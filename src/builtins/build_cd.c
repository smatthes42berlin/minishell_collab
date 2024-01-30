#include "minishell.h"

// clear the string from "./" an dubbel /
char *cler_str(char *path)
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

// return alltime NULL
char *buid_cd (t_node_exec *node)
{
	//printf("%s\n", getcwd(NULL,0));
	if (chdir(cler_str(node->argv[0])) == -1)
		error_code_handler(errno, "ERR-chdir", "CD -Command", "");
	printf("%s\n", getcwd(NULL,0));
	return (NULL);
}


t_node	*set_cd_absolut(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = buid_cd(test_cmd_exec("test pwd", "cd", "/home/rene/Project/42School/Rank03/minishell_collab/src", true));
	ret->type = EXEC;
	return (ret);
}

t_node	*set_cd_relativ(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = buid_cd(test_cmd_exec("test pwd", "cd", "src", true));
	ret->type = EXEC;
	return (ret);
}

t_node	*set_cd_relativ_revers(void)
{
	t_node	*ret;

	ret = malloc_handler(sizeof(t_node));
	ret->node_type = buid_cd(test_cmd_exec("test pwd", "cd", ".././././../////trash", true));
	ret->type = EXEC;
	return (ret);
}
