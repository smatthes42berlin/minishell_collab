#include "minishell.h"

int	set_program_name(void)
{
	t_main_data	*main_data;

	main_data = get_main_data();
	if (env_set_var(main_data, "PROGRAM_NAME=minishell"))
	{
		return (throw_error_custom((t_error_ms){errno, EPART_ENV, EFUNC_MALLOC,
				"env set exit code"}));
	}
	return (0);
}
