#include "minishell.h"

int	tokenise(t_main_data *main_data)
{
	char	*cur_pos;
	int		ret_check_synt;

	cur_pos = main_data->cli_input;
	skip_ws(&cur_pos);
	while (*cur_pos)
	{
		if (get_token(main_data, &cur_pos))
			return (1);
		skip_ws(&cur_pos);
	}
	ret_check_synt = check_syntax_n_heredoc(main_data);
	if (ret_check_synt == SIGINT + 128)
		return (SIGINT + 128);
	if (ret_check_synt)
		return (1);
	return (0);
}
