#include "minishell.h"

void	free_token(void *token)
{
	t_token	*token_cast;

	token_cast = token;
	free(token_cast->value);
	free(token);
}

void	free_main_exit(t_main_data *main_data, int program_state, int exit_code)
{
	if (program_state >= 1)
		free_str_arr_null(main_data->env_vars);
	if (program_state >= 2)
		free(main_data->cli_input);
	if (program_state >= 3)
		d_lst_clear(&main_data->token_list, free_token);
	init_main_data(main_data);
	if (exit_code >= 0)
		exit(exit_code);
}

int	free_heredoc_info_code(t_here_doc_info *hdoc_info, int code)
{
	free(hdoc_info->delim);
	return (code);
}
