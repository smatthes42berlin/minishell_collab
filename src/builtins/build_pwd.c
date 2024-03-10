#include "minishell.h"

char	**build_pwd(t_pipefd *pipefd)
{
	char	**ret_string;
	char	*str_tmp;
	char	*err_msg;

	err_msg = "function build_pwd";
	ret_string = use_malloc(sizeof(char *) * 2, err_msg);
	str_tmp = use_getcwd(err_msg);
	ret_string[0] = add_newline(str_tmp, true);
	ret_string[1] = NULL;
	free(str_tmp);
	pipefd->exit_code_buildin = 0;
	return (ret_string);
}

char	*use_getcwd(char *err_msg)
{
	char	*str_tmp;

	str_tmp = getcwd(NULL, 0);
	if (str_tmp == NULL)
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR,
			EFUNC_GETCWD, err_msg});
	return (str_tmp);
}
