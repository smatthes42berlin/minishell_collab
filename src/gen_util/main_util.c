#include "minishell.h"

bool	only_newline_entered(t_main_data *main_data)
{
	if (ft_strlen(main_data->cli_input) == 0)
		return (true);
	return (false);
}
