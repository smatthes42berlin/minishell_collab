#include "minishell.h"

char	*env_get_var(t_main_data *main_data, char *key)
{
	char	*var_val;

	var_val = ft_arr_char_get_val(main_data->env_vars, key);
	if (!var_val)
		return (ft_strdup(""));
	return (var_val);
}

// add string to array
// remove string from array
// copy array
// free array
// update array (remove + add)
// get elem index