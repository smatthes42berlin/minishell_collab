#include "minishell.h"

int	tokenise(t_main_data *main_data)
{
	char	*cur_pos;

	cur_pos = main_data->cli_input;
	while (*cur_pos)
	{
		printf("1\n");
		skip_ws(&cur_pos);
		create_token(&cur_pos, main_data);
	}
	return (1);
}

void	create_token(char **cur_pos, t_main_data *main_data)
{
	if (ft_strchr("\"", **cur_pos))
		creat_dquote_token(cur_pos, main_data);
	// else if (ft_strchr("'", **cur_pos))
	// 	creat_squote_token(cur_pos, main_data);
	// else if (is_symbol(**cur_pos))
	// 	create_symbol_token(cur_pos, main_data);
	// else
	// 	create_text_token(cur_pos, main_data);
}
