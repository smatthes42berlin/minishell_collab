#include "minishell.h"

static bool	is_system_call_error(t_error_ms error_info);

int	throw_error_custom(t_error_ms error_info)
{
	char	*res;

	res = NULL;
	set_exit_code(error_info.err_code);
	ft_printf_fd(2, "ERROR\n");
	if (is_system_call_error(error_info))
		ft_printf_fd(2, "errno msg: %s\n", strerror(error_info.err_code));
	ft_printf_fd(2, "Program Part: %s\n",
		get_program_part_str(error_info.program_part));
	ft_printf_fd(2, "Failed Func: %s\n",
		get_failed_func_str(error_info.failed_func));
	if (error_info.add_info)
		ft_printf_fd(2, "Add Info: %s\n", error_info.add_info);
	free(res);
	return (error_info.err_code);
}

int	throw_error_mimic_bash(char *msg, int code)
{
	set_exit_code(code);
	ft_printf_fd(2, "%s\n", msg);
	return (code);
}

static bool	is_system_call_error(t_error_ms error_info)
{
	return (error_info.failed_func != EFUNC_DEV_ISSUE
		&& error_info.failed_func != EFUNC_INPUT_ERROR);
}
