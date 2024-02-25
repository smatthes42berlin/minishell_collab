#include "minishell.h"

int	init_env_vars(t_main_data *main_data, char *envp[])
{
	main_data->env_vars = ft_arr_cpy_char_null(envp);
	if (!main_data->env_vars)
		return (throw_error_custom((t_error_ms){errno, EPART_ENV, EFUNC_MALLOC,
				"init env vars"}));
	if (set_exit_code(0))
		return (1);
	if (set_program_name())
		return (1);
	return (0);
}
