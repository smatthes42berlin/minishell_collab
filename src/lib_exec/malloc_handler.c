#include "minishell.h"

void    *use_malloc(size_t bytes, char *err_msg)
{
	void    *ret;

	ret = malloc(bytes);
	if (ret == NULL && PRINT_CUSTOM_ERR)
    {
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
            err_msg});
    }
    return (ret);
}