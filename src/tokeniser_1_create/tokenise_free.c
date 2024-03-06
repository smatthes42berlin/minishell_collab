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

int	free_main_exit_end_of_loop(t_main_data *main_data)
{
	free(main_data->cli_input);
	d_lst_clear(&main_data->token_list, free_token);
	free_ast(main_data->ast);
	reset_main_data(main_data, false);
	return (0);
}

void	free_main_exit(t_main_data *main_data, int exit_code)
{
	int	last_exit;

	if (exit_code > 0)
		last_exit = exit_code;
	else
		last_exit = get_exit_code();
	free_str_arr_null(main_data->env_vars);
	free(main_data->cli_input);
	d_lst_clear(&main_data->token_list, free_token);
	rl_clear_history();
	free_ast(main_data->ast);
	reset_main_data(main_data, true);
	if (exit_code)
		exit(last_exit);
}

int	free_heredoc_info_code(t_here_doc_info *hdoc_info, int code)
{
	free(hdoc_info->compl_str);
	free(hdoc_info->delim);
	return (code);
}
