#include "minishell.h"

char	*add_newline(char *str, bool newline)
{
	char	*ret;
	char	*err_msg;

	err_msg = "function add_newline!";
	ret = NULL;
	if (newline)
		ret = use_strjoin(str, "\n", err_msg);
	else
		ret = use_strdup(str, err_msg);
	return (ret);
}

static char	**creat_str_arr(char **arg, int i_beginn)
{
	int		i_count;
	char	**ret;
	char	*err_msg;

	err_msg = "function creat_str_arr for copy_str_arr function";
	i_count = i_beginn;
	while (arg[i_count] != NULL)
		i_count++;
	ret = use_malloc(sizeof(char *) * (i_count - i_beginn + 1), err_msg);
	if (!ret)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
			err_msg});
	ret[i_count - i_beginn] = NULL;
	return (ret);
}

char	**copy_str_arr(char **arg, int i_beginn, bool newline)
{
	int		i_count;
	char	**ret;
	char	*str_tmp;
	char	*err_msg;

	err_msg = "function copy_str_arr";
	ret = creat_str_arr(arg, i_beginn);
	i_count = i_beginn;
	while (arg[i_count] != NULL)
	{
		str_tmp = use_strdup(arg[i_count], err_msg);
		if (newline)
			ret[i_count - i_beginn] = use_strjoin(str_tmp, "\n", err_msg);
		else
			ret[i_count - i_beginn] = use_strdup(str_tmp, err_msg);
		free(str_tmp);
		str_tmp = NULL;
		i_count++;
	}
	return (ret);
}

bool	check_bash_variable(char *str)
{
	int	i_count;
	int	len_var_name;

	i_count = 0;
	if (ft_isdigit(str[i_count]) || (str[i_count] == '='))
		return (false);
	if (ft_strchr(str, '=') == NULL)
		len_var_name = ft_strlen(str);
	else
		len_var_name = ft_strlen(str) - ft_strlen(ft_strchr(str, '='));
	while (str[i_count] != '\0' && i_count < len_var_name)
	{
		if (!ft_isalnum(str[i_count]) && (str[i_count]) != '_'
			&& (str[i_count] != '='))
			return (false);
		i_count++;
	}
	return (true);
}

// void	write_exit_code_0(t_pipefd *pipefd, char *err_msg)
// {
// 	char	**ret;

// 	ret = use_malloc(sizeof(char *) * 2, err_msg);
// 	ret[0] = use_strjoin(EXIT_CODE, "exit=0", err_msg);
// 	ret[1] = NULL;
// 	write_pipe_to_executor_pipe(pipefd->pipefd, ret, "function \"build_cd\"");
// 	free_str_arr_null(ret);
// }

bool	check_flag_err_buildin(t_pipefd *pipefd, char **arg, char *err_msg)
{
	char	*tmp_str_1;
	char	*tmp_str_2;

	if (arg[1] != NULL && arg[1][0] == '-' && arg[1][1] != '\0')
	{
		tmp_str_1 = use_strjoin("minishell: ", arg[0], err_msg);
		tmp_str_2 = use_strjoin(tmp_str_1, ": ", err_msg);
		free(tmp_str_1);
		tmp_str_1 = use_strjoin(tmp_str_2, arg[1], err_msg);
		free(tmp_str_2);
		tmp_str_2 = use_strjoin(tmp_str_1, ": invalid option", err_msg);
		ft_printf_fd(2, "%s\n", tmp_str_2);
		free(tmp_str_1);
		free(tmp_str_2);
		pipefd->exit_code_buildin = 2;
		return (true);
	}
	pipefd->exit_code_buildin = 0;
	return (false);
}
