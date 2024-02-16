#include "minishell.h"

int	check_heredoc(t_list_d **cur_token)
{
	t_list_d		*next_token;
	t_token			*cur_token_val;
	t_token			*next_token_val;
	t_here_doc_info	hdoc_info;

	cur_token_val = (*cur_token)->content;
	if (cur_token_val->type != T_DLESS)
		return (0);
	next_token = (*cur_token)->next;
	next_token_val = next_token->content;
	init_hdoc_info(next_token_val->value, &hdoc_info);
	if (check_heredoc_delim(&hdoc_info))
		return (free_heredoc_info_code(&hdoc_info, 1));
	if (read_heredoc(&hdoc_info, cur_token))
		return (free_heredoc_info_code(&hdoc_info, 2));
	return (free_heredoc_info_code(&hdoc_info, 0));
}

void	init_hdoc_info(char *delim_raw, t_here_doc_info *hdoc_info)
{
	hdoc_info->delim = NULL;
	hdoc_info->delim_raw = delim_raw;
	hdoc_info->quoted = false;
	hdoc_info->num_char_no_quote = 0;
	hdoc_info->index_close_quote = 0;
	hdoc_info->tmp = NULL;
}