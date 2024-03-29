#include "minishell.h"

static void	check_equal_sign_in_str_arr(char **arg, t_pipefd *pipefd);
static void	clr_str(char **str);

char	**build_export(t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char	**ret;
	char	*err_msg;

	err_msg = "function build_export";
	if (data->ast->type == PIPE)
		return (NULL);
	ret = copy_str_arr(node->argv, 0, false);
	check_equal_sign_in_str_arr(ret, pipefd);
	write_pipe_to_executor_pipe(pipefd->pipefd, ret, err_msg);
	free_str_arr_null(ret);
	return (NULL);
}

static char	*char_err_messag_exit(char *arg, char *err_msg)
{
	char	*ret;
	char	*str_tmp;

	ret = use_strjoin(EXIT_CODE, "_MSG=minishell: \'", err_msg);
	str_tmp = use_strjoin(ret, arg, err_msg);
	free(ret);
	ret = use_strjoin(str_tmp, "\': not a valid identifier", err_msg);
	free(str_tmp);
	return (ret);
}

static void	check_equal_sign_in_str_arr(char **arg, t_pipefd *pipefd)
{
	int		i_count;
	char	*err_msg;
	char	*str_tmp;

	pipefd->exit_code_buildin = 0;
	err_msg = "function check_equal_sign_in_str_arr -> build export";
	i_count = 1;
	while (arg[i_count] != NULL)
	{
		if (!check_bash_variable(arg[i_count]))
		{
			str_tmp = use_strdup(arg[i_count], err_msg);
			free(arg[i_count]);
			arg[i_count] = NULL;
			arg[i_count] = char_err_messag_exit(str_tmp, err_msg);
			free(str_tmp);
			pipefd->exit_code_buildin = 1;
			break ;
		}
		clr_str(&arg[i_count]);
		i_count++;
	}
}

static void	clr_str(char **str)
{
	char	*tmp_str;
	char	*err_msg;

	err_msg = "function clr_str -> build export";
	if (ft_strchr(*str, '=') == NULL)
	{
		free(*str);
		*str = NULL;
		return ;
	}
	else
	{
		tmp_str = use_strdup(*str, err_msg);
		free(*str);
		*str = NULL;
		*str = use_strjoin(ADD_ENV, tmp_str, err_msg);
		free(tmp_str);
		tmp_str = NULL;
	}
}
