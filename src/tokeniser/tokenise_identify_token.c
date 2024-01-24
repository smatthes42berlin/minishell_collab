#include "minishell.h"

void	skip_ws(char **cur_pos)
{
	while (ft_isspace(**cur_pos) && **cur_pos)
	{
		(*cur_pos)++;
	}
}

char	*is_symbol(char c)
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
