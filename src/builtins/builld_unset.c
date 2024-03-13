#include "minishell.h"

static	void	add_clr_command_to_arr_str(t_main_data *data,
					char **arg);
static	char	*check_is_env(t_main_data *data, char *arg, char *err_msg);

char	**build_unset(t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char	**ret;

	if (data->ast->type == PIPE)
	{
		return (NULL);
	}
	ret = copy_str_arr(node->argv, 0, false);
	add_clr_command_to_arr_str(data, ret);
	write_pipe_to_executor_pipe(pipefd->pipefd, ret, "function \"build_cd\"");
	free_str_arr_null(ret);
	return (NULL);
}

static void	add_clr_command_to_arr_str(t_main_data *data, char **arg)
{
	int		i_count;
	char	*tmp_str;
	char	*err_msg;

	i_count = 1;
	err_msg = "function add_clr_command_to_arr_str -> build unset";
	while (arg[i_count] != NULL)
	{
		tmp_str = check_is_env(data, arg[i_count], err_msg);
		free(arg[i_count]);
		arg[i_count] = NULL;
		if (str_are_equal (tmp_str, ""))
			arg[i_count] = use_strdup(tmp_str, err_msg);
		else
			arg[i_count] = use_strjoin(CLR_ENV, tmp_str, err_msg);
		free(tmp_str);
		tmp_str = NULL;
		i_count++;
	}
}

static char	*check_is_env(t_main_data *data, char *arg, char *err_msg)
{
	char	*ret;

	if (ft_strchr(arg, '=') != NULL)
	{
		ret = use_strdup("noting", err_msg);
	}
	else
	{
		if (str_are_equal(env_get_var(data, arg), ""))
			ret = use_strdup("noting", err_msg);
		else
			ret = use_strdup(arg, err_msg);
	}
	return (ret);
}
