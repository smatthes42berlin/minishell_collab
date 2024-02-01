#include "minishell.h"

void	skip_ws(char **cur_pos)
{
	while (ft_isspace(**cur_pos) && **cur_pos)
		(*cur_pos)++;
}

char	*is_operator(char c)
{
	return (ft_strchr("<>|", c));
}

char	*is_squote(char c)
{
	return (ft_strchr("'", c));
}

char	*is_dquote(char c)
{
	return (ft_strchr("\"", c));
}

int	has_closing_quote(char *cli_input, char quote_type)
{
	return (ft_str_chr_index(cli_input, quote_type));
}
