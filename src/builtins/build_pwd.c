#include "minishell.h"

char	**build_pwd(bool newline)
{
	char	**ret;
	char	*str_tmp;
	char	*err_msg;

	err_msg = "function build_pwd";
	print_debugging_info_executer(INT_DEBUG, 24, NULL);
	ret = use_malloc(sizeof(char *) * 2, err_msg);
	str_tmp = getcwd(NULL, 0);
	if (str_tmp == NULL)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_GETCWD,
			"function \"build_pwd\" for \'pwd\' command!"});
	ret[0] = add_newline(str_tmp, newline);
	ret[1] = NULL;
	free(str_tmp);
	return (ret);
}
