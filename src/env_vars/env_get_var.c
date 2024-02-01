#include "minishell.h"

char	*env_get_var(t_main_data *main_data, char *key)
{
	return (ft_arr_char_get_val(main_data->env_vars, key));
}

// add string to array
// remove string from array
// copy array
// free array
// update array (remove + add)
// get elem index