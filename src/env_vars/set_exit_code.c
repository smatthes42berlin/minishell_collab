#include "minishell.h"

int	set_exit_code(int code)
{
	char *res;
	t_main_data *main_data;

	main_data = get_main_data();
	res = NULL;

	if (ft_printf_to_str(&res, "MINISHELL_LAST_EXIT=%d", code) ==
		-1)
	{
		return (throw_error_custom((t_error_ms){errno, EPART_ENV, EFUNC_MALLOC,
				"env set exit code"}));
	}
	if (env_set_var(main_data, res))
	{
		return (throw_error_custom((t_error_ms){errno, EPART_ENV, EFUNC_MALLOC,
				"env set exit code"}));
	}
	return (0);
}