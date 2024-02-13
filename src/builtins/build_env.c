#include "minishell.h"

char	**build_env(t_main_data *data)
{
	print_debugging_info_executer(INT_DEBUG, 28, NULL);
	if (data->ast->type == PIPE)
	{
		return (data->env_vars);
	}
	else
		print_str_arr_null(data->env_vars);
	return (NULL);
}