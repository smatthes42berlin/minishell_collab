#include "minishell.h"

int	tokenise(t_main_data *main_data)
{
	char	*cur_pos;

	cur_pos = main_data->cli_input;
    cur_pos++;
	return 1;
	// while (*cur_pos)
	// {
	// 	skip_ws(&cur_pos);
	// 	create_token(&cur_pos, main_data);
	// }
}

// void	create_token(char **cur_pos, t_list *token_list)
// {
// 	if (ft_strchr("\"", **cur_pos))
// 		creat_dquote_token(cur_pos, token_list);
// 	else if (ft_strchr("'", **cur_pos))
// 		creat_squote_token(cur_pos, token_list);
// 	else if (is_symbol(**cur_pos))
// 		create_symbol_token(cur_pos, token_list);
// 	else
// 		create_text_token(cur_pos, token_list);
// }

// void	del_token(void *data)
// {
// 	struct s_token	*token;

// 	token = data;
// 	free(token->value);
// }

// void	creat_dquote_token(char **cur_pos, t_list *token_list)
// {
// 	*t_list ft_lstnew();
// }

