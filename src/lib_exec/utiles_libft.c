#include "minishell.h"

char *use_strjoin(char const *s1, char const *s2, char *err_msg)
{
    char    *ret;

    ret = ft_strjoin(s1, s2);
    if (ret == NULL)
        throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
            err_msg});
    return (ret);
}