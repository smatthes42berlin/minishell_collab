#include "minishell.h"

int	env_set_var(t_main_data *main_data, char *val)
{
	char	**new_env;

	new_env = ft_arr_char_add_replace_n(main_data->env_vars, val);
	free_str_arr_null(main_data->env_vars);
	if (!new_env)
	{
		printf("Error: adding env var!\n");
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