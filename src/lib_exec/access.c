#include "minishell.h"

int	access_handler(const char *path, enum e_access_mode mode, int debug_mode)
{
	int	result;

	result = -1;
	if (FILE_EXISTS == mode || FILE_READABLE == mode || FILE_WRITABLE == mode
		|| FILE_EXECUTABLE == mode)
	{
		result = access(path, mode);
		if (result < 0 && debug_mode)
			throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_ACCESS,
				"function \"access_handler\""});
	}
	else
	{
		printf("ERROR 'access' - Wrong Mode given\n");
		return (result);
	}
	return (result);
}
