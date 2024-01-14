#include "minishell.h"

int	count_symbols(char *cur_pos)
{
	int	num;

	num = 0;
	while (is_symbol(cur_pos[num]) && cur_pos[num])
		num++;
	return (num);
}

int	count_characters(char *cur_pos)
{
	int	num;

	num = 0;
	while (!is_symbol(cur_pos[num]) && !ft_isspace(cur_pos[num])
		&& cur_pos[num])
		num++;
	return (num);
}

int	symbol_is_valid(char *symbol, int symbol_length)
{
	if (is_symbol(*symbol) && symbol_length == 1)
		return (0);
	if (symbol[0] == '<' && symbol[1] != '<')
		return (1);
	if (symbol[0] == '>' && symbol[1] != '>')
		return (1);
	if (symbol_length >= 3)
		return (2);
	return (0);
}
