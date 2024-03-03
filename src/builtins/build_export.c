#include "minishell.h"

static void	check_equal_sign_in_str_arr(char **arg);
static void	clr_str(char **str);

char	**build_export(t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char	**ret;
	char	*err_msg;

	err_msg = "function build_export";
	print_debugging_info_executer(INT_DEBUG, 26, NULL);
	if (data->ast->type == PIPE)
		return (NULL);
	ret = copy_str_arr(node->argv, 0, false);
	check_equal_sign_in_str_arr(ret);
	//print_str_arr_null(ret);
	write_pipe_to_executor_pipe(pipefd->pipefd, ret, err_msg);
	return (NULL);
}

static void	check_equal_sign_in_str_arr(char **arg)
{
	int		i_count;
	char	*err_msg;
	bool	exit_0;

	exit_0 = true;
	err_msg = "function check_equal_sign_in_str_arr -> build export";
	i_count = 0;
	while (arg[i_count] != NULL)
	{
		if (!check_bash_variable(arg[i_count]))
		{
			free(arg[i_count]);
			arg[i_count] = NULL;
			arg[i_count] = use_strjoin(EXIT_CODE,
					"exit=1_MSG=minishell: export: not a valid identifier",
					err_msg);
			exit_0 = false;
			break ;
		}
		clr_str(&arg[i_count]);
		i_count++;
	}
	if (exit_0)
		arg[0] = use_strjoin(EXIT_CODE, "exit=0", err_msg);
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
		*str = "";
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
