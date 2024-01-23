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
	printf("dsf\n");
	check_syntax_n_heredoc(main_data);
	print_token_list(main_data->token_list);
	main_data->token_list = NULL;
	return (1);
}


