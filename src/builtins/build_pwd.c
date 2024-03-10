#include "minishell.h"

char	**build_pwd(t_main_data *data, t_node_exec *node,
		t_pipefd *pipefd)
{
	char	**ret_string;
	char	*str_tmp;
	char	*err_msg;

	if (!data && !node && !pipefd)
		printf("NOt");

	err_msg = "function build_pwd";
	ret_string = use_malloc(sizeof(char *) * 2, err_msg);
	str_tmp = use_getcwd(err_msg);
	ret_string[0] = add_newline(str_tmp, true);
	ret_string[1] = NULL;
	free(str_tmp);
	pipefd->exit_code_buildin = 0;
	// if (is_last_node_exec(data->ast, node->file_path) && !from_redir)
	// 	write_exit_code_0(pipefd, err_msg);
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
