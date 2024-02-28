#include "minishell.h"

static int	ft_atoi_byte(const char *nptr);
static char	**check_arg(char **str_arr);
static char	**bigger_two_arg(void);
static char *ret_exit_code_line(int nbr);

char	**build_exit(t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char	**ret;

	print_debugging_info_executer(INT_DEBUG, 31, NULL);
	if (data->ast->type == PIPE)
	{
		return (NULL);
	}
	ret = check_arg(node->argv);
	write_pipe_to_executor_pipe(pipefd->pipefd, ret,
		"function \"build_export\"");
	return (NULL);
}

static char	**check_arg(char **str_arr)
{
	char			**ret;
	int				nbr;
	char			*err_msg;

	err_msg = "function check_arg -> build_exit";
	nbr = 0;
	while (str_arr[nbr] != NULL)
	{
		if (nbr > 1)
			return (bigger_two_arg());
		nbr++;
	}
	if (nbr == 1)
		nbr = 0;
	else
		nbr = ft_atoi_byte(str_arr[1]);
	ret = use_malloc(sizeof(char *) * 3, err_msg);
	ret[0] = ret_exit_code_line(nbr);
	ret[1] = use_strdup(EXIT, err_msg);
	ret[2] = NULL;
	return (ret);
}


static char *ret_exit_code_line(int nbr)
{
	char 			*ret;
	unsigned char	exit_number;
	char			*str_e_number;
	char			*str_tmp;
	char			*err_msg;

	err_msg = "function ret_exit_code_line -> build exit";
	if (nbr == -2)
		ret = use_strjoin(EXIT_CODE,
				"exit=2_MSG=minishell: exit: numeric argument required",
				err_msg);
	else
	{
		exit_number = nbr;
		str_e_number = ft_itoa(exit_number);
		str_tmp = use_strjoin("exit=", str_e_number, err_msg);
		ret = use_strjoin(EXIT_CODE, str_tmp, err_msg);
		free(str_e_number);
		free(str_tmp);
	}
	return (ret);
}

// special atoi 
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

static char	**bigger_two_arg(void)
{
	char	**ret;
	char	*err_msg;

	err_msg = "function bigger_two_arg --> exit cmd";
	ret = use_malloc(sizeof(char *) * 2, err_msg);
	ret[0] = use_strjoin(EXIT_CODE, "exit=1_MSG=exit: too many arguments",
			err_msg);
	ret[1] = NULL;
	return (ret);
}