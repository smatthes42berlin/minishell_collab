#include "minishell.h"

int	env_del_var(t_main_data *main_data, char *val)
{
	char	**new_env;

	new_env = ft_arr_char_rem_n(main_data->env_vars, val);
	free_str_arr_null(main_data->env_vars);
	if (!new_env)
	{
		printf("Error: deleting env var!\n");
		return (1);
	}
	main_data->env_vars = new_env;
	return (0);
}

// add string to array
// remove string from array
// copy array
// free array
// update array (remove + add)
// get elem index