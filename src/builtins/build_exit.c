#include "minishell.h"

static int	ft_atoi_byte(const char *nptr);
static char	**check_arg(char **str_arr, bool exit, t_pipefd *pipefd);
static char	**bigger_two_arg(t_pipefd *pipefd);
static char	*ret_exit_code_line(int nbr, char **str_arr, t_pipefd *pipefd);

char	**build_exit(t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char	**ret;

	if (is_last_node_exec(data->ast, node->file_path)
		&& data->ast->type == PIPE)
		ret = check_arg(node->argv, false, pipefd);
	else
		ret = check_arg(node->argv, true, pipefd);
	write_pipe_to_executor_pipe(pipefd->pipefd, ret,
		"function \"build_export\"");
	free_str_arr_null(ret);
	return (NULL);
}

static char	**check_arg(char **str_arr, bool exit, t_pipefd *pipefd)
{
	char			**ret;
	int				nbr;
	char			*err_msg;

	err_msg = "function check_arg -> build_exit";
	nbr = 0;
	while (str_arr[nbr] != NULL)
	{
		if (nbr > 1 && ft_atoi_byte(str_arr[1]) != -2)
			return (bigger_two_arg(pipefd));
		nbr++;
	}
	if (nbr == 1)
		nbr = 0;
	else
		nbr = ft_atoi_byte(str_arr[1]);
	ret = use_malloc(sizeof(char *) * 3, err_msg);
	ret[0] = ret_exit_code_line(nbr, str_arr, pipefd);
	ret[1] = ret_exit_err(exit, err_msg);
	ret[2] = NULL;
	return (ret);
}

static char	*ret_exit_code_line(int nbr, char **str_arr, t_pipefd *pipefd)
{
	unsigned char	exit_number;
	char			*str_tmp;
	char			*err_msg;
	char			*ret;

	str_tmp = NULL;
	err_msg = "function ret_exit_code_line -> build exit";
	if (nbr == -2)
	{
		ret = use_strjoin(EXIT_CODE,
				"_MSG=minishell: exit: ", err_msg);
		str_tmp = use_strjoin(ret, str_arr[1], err_msg);
		free(ret);
		ret = use_strjoin(str_tmp, ": numeric argument required", err_msg);
		pipefd->exit_code_buildin = 2;
	}
	else
	{
		exit_number = nbr;
		pipefd->exit_code_buildin = exit_number;
		ret = use_strdup("EMPTY", err_msg);
	}
	free(str_tmp);
	return (ret);
}

static int	ft_atoi_byte(const char *nptr)
{
	int				sign;
	int				res;
	size_t			i;
	unsigned char	ret;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	if (ft_strlen(nptr) == 1 && ft_isdigit(nptr[0]) == 0)
		return (-2);
	while (ft_isdigit(nptr[i]) != 0)
		res = res * 10 + nptr[i++] - '0';
	if (ft_strlen(nptr) != i)
		return (-2);
	ret = (res * sign) % 256;
	return (ret);
}

static char	**bigger_two_arg(t_pipefd *pipefd)
{
	char	**ret;
	char	*err_msg;

	err_msg = "function bigger_two_arg --> exit cmd";
	ret = use_malloc(sizeof(char *) * 2, err_msg);
	ret[0] = use_strjoin(EXIT_CODE, "_MSG=exit: too many arguments",
			err_msg);
	ret[1] = NULL;
	pipefd->exit_code_buildin = 1;
	return (ret);
}
