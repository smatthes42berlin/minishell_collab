#include "minishell.h"

void	skip_ws(char **cur_pos)
{
	while (ft_isspace(**cur_pos) && **cur_pos)
		(*cur_pos)++;
}

int	has_closing_quote(char *cli_input, char quote_type)
{
	return (ft_str_chr_index(cli_input, quote_type));
}

int	count_operators(char *cur_pos)
{
	int	num;

	num = 0;
	while (is_operator(cur_pos[num]) && cur_pos[num])
		num++;
	return (num);
}

int	count_characters(char *cur_pos)
{
	int	num;
	int	closing_quote;

	num = 0;
	while (!is_operator(cur_pos[num]) && !ft_isspace(cur_pos[num])
		&& cur_pos[num])
	{
		if (is_dquote(cur_pos[num]))
		{
			closing_quote = has_closing_quote(&(cur_pos[num + 1]), '"');
			if (closing_quote == -1)
				return (-1);
			num = num + closing_quote + 1;
		}
		else if (is_squote(cur_pos[num]))
		{
			closing_quote = has_closing_quote(&(cur_pos[num + 1]), '\'');
			if (closing_quote == -1)
				return (-1);
			num = num + closing_quote + 1;
		}
		num++;
	}
	return (num);
}
