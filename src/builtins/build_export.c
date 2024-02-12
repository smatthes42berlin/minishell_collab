#include "minishell.h"

static void check_equal_sign_in_str_arr(char **arg);

char	**build_export(t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char	**ret;

	print_debugging_info_executer(INT_DEBUG, 26, NULL);
	ret = copy_str_arr(node->argv, 1);
	check_equal_sign_in_str_arr(ret);
	pipe_setting(pipefd->pipefd, true ,ret);
	return (NULL);
}

static void check_equal_sign_in_str_arr(char **arg)
{
	int i_count;
	char *tmp_str;

	i_count = 0;
	while(arg[i_count] != NULL)
	{
		if (ft_strchr(arg[i_count], '=') == NULL)
		{
			free(arg[i_count]);
			arg[i_count] = ft_strdup("");
		}
		else
		{
			tmp_str = ft_strdup(arg[i_count]);
			free(arg[i_count]);
			arg[i_count] = NULL;
			arg[i_count] = ft_strjoin(ADD_ENV, tmp_str);
			free(tmp_str);
            tmp_str = NULL;
		}
		i_count++;
	}
}

