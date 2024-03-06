#include "minishell.h"

static char	*ret_absoult(void);
static char	*ret_relativ(void);
static char	*ft_clear_str(char *path);

char	*check_cd_argument(t_main_data *data, t_node_exec *node)
{
	char	*str_tmp;

	if (node->argv[1] == NULL)
		str_tmp = env_get_var(data, "HOME");
	else if (str_are_equal(node->argv[1], "-"))
		str_tmp = ft_clear_str("..");
	else 
		str_tmp = ft_clear_str(node->argv[1]);
	return (str_tmp);
}

char	*absoult_or_relativ_path(char *path)
{
	char	*ret;

	ret = NULL;
	if (path[0] == '/')
		ret = ret_absoult();
	else
		ret = ret_relativ();
	return (ret);
}

static char	*ret_absoult(void)
{
	char	*ret;
	char	*err_msg;

	err_msg = "function \"absoult_or_relativ_path\" -> \"ret_absoult\" -> cd";
	ret = NULL;
	ret = malloc(sizeof(char) * 2);
	if (!ret)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
			err_msg});
	else
	{
		ret[0] = '/';
		ret[1] = '\0';
	}
	return (ret);
}

static char	*ret_relativ(void)
{
	char	*ret;
	char	*err_msg;

	err_msg = "function \"absoult_or_relativ_path\" -> \"ret_relativ\" -> cd";
	ret = NULL;
	ret = malloc(sizeof(char));
	if (!ret)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
			err_msg});
	else
		ret[0] = '\0';
	return (ret);
}

// clear the string from "./" an double /
static char	*ft_clear_str(char *path)
{
	int		i;
	char	**str;
	char	*ret;
	char	*str_tmp;
	char	*err_msg;

	err_msg = "function \"ft_clear_str\" for build cd";
	print_debugging_info_executer(INT_DEBUG, 25, NULL);
	i = -1;
	ret = absoult_or_relativ_path(path);
	str = ft_split_str(path, "/");
	while (str[++i] != NULL)
	{
		if (ft_strncmp(str[i], ".", ft_strlen(".")) == 0 && str[i][1] == '\0')
			;
		else
		{
			str_tmp = use_strjoin(ret, str[i], err_msg);
			free(ret);
			ret = use_strjoin(str_tmp, "/", err_msg);
			free(str_tmp);
		}
	}
	free_str_arr_null(str);
	return (ret);
}
