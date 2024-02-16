#include "minishell.h"

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

char	*is_dollar_char(char c)
{
	return (ft_strchr("$", c));
}

bool	is_valid_var_name_char(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}
