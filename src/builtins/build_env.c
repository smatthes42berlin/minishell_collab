#include "minishell.h"

char	**build_env(t_main_data *data)
{
	char **ret;

	print_debugging_info_executer(INT_DEBUG, 28, NULL);
	ret = copy_str_arr(data->env_vars, 0, true);
	print_str_arr_null(ret);
	return (ret);
}