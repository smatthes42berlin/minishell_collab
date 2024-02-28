#include "minishell.h"

static int	ft_atoi_byte(const char *nptr);
static char	**check_arg(char **str_arr);
static char	**bigger_two_arg(void);

char	**build_exit(t_main_data *data, t_node_exec *node, t_pipefd *pipefd)
{
	char	**ret;

	print_debugging_info_executer(INT_DEBUG, 31, NULL);
	if (data->ast->type == PIPE)
	{
		return (NULL);
	}
	ret = check_arg(node->argv);
	//print_str_arr_null(ret);
	write_pipe_to_executor_pipe(pipefd->pipefd, ret,
		"function \"build_export\"");
	return (NULL);
}

static char	**check_arg(char **str_arr)
{
	char			**ret;
	int				nbr;
	unsigned char	exit_number;
	char			*str_e_number;
	char			*str_tmp;

	nbr = 0;
	while (str_arr[nbr] != NULL)
	{
		if (nbr > 1)
			return (bigger_two_arg());
		nbr++;
	}
//	printf("arrays cunt%i\n", nbr);
	if (nbr == 1)
		nbr = 0;
	else
		nbr = ft_atoi_byte(str_arr[1]);
//	printf("return value%i\n", nbr);
	ret = malloc(sizeof(char *) * 4);
	if (nbr == -2)
		ret[0] = ft_strjoin(EXIT_CODE,
				"exit=2_MSG=minishell: exit: numeric argument required");
	else
	{
		exit_number = nbr;
		str_e_number = ft_itoa(exit_number);
		str_tmp = ft_strjoin("exit=", str_e_number);
		ret[0] = ft_strjoin(EXIT_CODE, str_tmp);
		free(str_e_number);
		free(str_tmp);
	}
	ret[1] = ft_strdup(EXIT);
	ret[2] = ft_strdup("BULLSHITT NOTHG");
	ret[3] = NULL;
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

static char	**bigger_two_arg(void)
{
	char **ret;

	ret = malloc(sizeof(char *) * 2);
	ret[0] = ft_strjoin(EXIT_CODE, "exit=1_MSG=exit: too many arguments");
	ret[1] = NULL;
	return (ret);
}