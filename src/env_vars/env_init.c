#include "minishell.h"

int	init_env_vars(t_main_data *main_data, char *envp[])
{
	main_data->env_vars = ft_arr_char_add_replace_n(envp,
			"MINISHELL_LAST_EXIT=0");
	if (!main_data->env_vars)
		return (throw_error_custom((t_error_ms){errno, EPART_ENV, EFUNC_MALLOC,
				"init env vars"}));
	return (0);
}
