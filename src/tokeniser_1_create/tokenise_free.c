#include "minishell.h"

void	free_token(void *token)
{
	t_token	*token_cast;

	if (!token)
		return ;
	token_cast = token;
	free(token_cast->value);
	free(token);
}

void	free_main_exit(t_main_data *main_data, int exit_code)
{
	free_str_arr_null(main_data->env_vars);
	free(main_data->cli_input);
	d_lst_clear(&main_data->token_list, free_token);
	reset_main_data(main_data);
	rl_clear_history();
	if (exit_code >= 0)
		exit(exit_code);
}

int	free_heredoc_info_code(t_here_doc_info *hdoc_info, int code)
{
	free(hdoc_info->delim);
	return (code);
}
