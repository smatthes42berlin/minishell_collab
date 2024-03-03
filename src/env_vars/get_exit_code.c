#include "minishell.h"

int	get_exit_code(void)
{
	char		*res;
	int			code;
	t_main_data	*main_data;

	main_data = get_main_data();
	if (!main_data->env_vars)
		return (0);
	res = env_get_var(main_data, "MINISHELL_LAST_EXIT");
	if (!res)
		return (throw_error_custom((t_error_ms){errno, EPART_ENV, EFUNC_MALLOC,
				"env get exit code"}));
	code = ft_atoi(res);
	free(res);
	return (code);
}
