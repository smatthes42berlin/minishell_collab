#include "minishell.h"

static  char    *ret_absoult(void);
static  char    *ret_relativ(void);

char	*absoult_or_relativ_path(char *path)
{
	char *ret;

	ret = NULL;
	if (path[0] == '/')
        ret = ret_absoult();
	else
        ret = ret_relativ();
	return (ret);
}

static  char    *ret_absoult(void)
{
    char    *ret;
    char    *err_msg;

	err_msg = "function \"absoult_or_relativ_path\" -> \"ret_absoult\" -> cd";
    ret = NULL;
	ret = malloc(sizeof(char) * 2);
	if (!ret)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
			err_msg});
	else
	{
		ret[0] = '/';
		ret[1] = '\0';
	}
    return(ret);
}

static  char    *ret_relativ(void)
{
    char    *ret;
    char    *err_msg;

	err_msg = "function \"absoult_or_relativ_path\" -> \"ret_relativ\" -> cd";
    ret = NULL;
    ret = malloc(sizeof(char));
    if (!ret)
        throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_MALLOC,
            err_msg});
    else
        ret[0] = '\0';
    return (ret);
}