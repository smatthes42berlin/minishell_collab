#include "minishell.h"

int	check_syntax_n_heredoc(t_main_data *main_data)
{
	t_list_d	**cur_token;

	cur_token = &main_data->token_list;
	while ((*cur_token)->next)
	{
		
		if (check_syntax((*cur_token)))
			return (1);
		if (check_heredoc(main_data, cur_token))
			return (2);
		cur_token = &(*cur_token)->next;
	}
	if (check_syntax(*cur_token))
		return (1);
	remove_here_doc_token(main_data);
	return (0);
}
