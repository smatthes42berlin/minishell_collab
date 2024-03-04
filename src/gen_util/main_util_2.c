#include "minishell.h"

int	token_lst_is_empty(t_main_data *main_data)
{
	if (!main_data->token_list)
	{
		if (set_exit_code(0))
			return (-1);
		return (1);
	}
	return (0);
}
