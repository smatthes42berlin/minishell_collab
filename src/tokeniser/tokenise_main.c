
#include "minishell.h"

// check operators directly for syntax errors
// start heredoc driectly when recognised

int	tokenise(t_main_data *main_data)
{
	char	**cur_pos;

	cur_pos = &main_data->cli_input;
	skip_ws(cur_pos);
	while (**cur_pos)
	{
		if (get_token(main_data, cur_pos))
			return (printf("ERROR\n"));
		skip_ws(cur_pos);
	}
	print_token_list(main_data->token_list);
	main_data->token_list = NULL;
	return (1);
}

int	get_token(t_main_data *main_data, char **cur_pos)
{
	t_token	*new_token;

	new_token = create_token();
	if (!new_token)
		return (printf("Token creation Error!\n"));
	if (append_token_list(main_data, new_token))
		return (printf("Error appending Token to list!\n"));
	if (identify_token(cur_pos, new_token))
		return (1);
	return (0);
}
