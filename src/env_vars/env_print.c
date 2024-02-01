#include "minishell.h"

void	env_print(t_main_data *main_data)
{
	print_str_arr_null(main_data->env_vars);
}

// add string to array
// remove string from array
// copy array
// free array
// update array (remove + add)
// get elem index