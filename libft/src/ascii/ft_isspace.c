#include "lib_main.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n')
		return (1);
	if (c == '\v' || c == '\t')
		return (1);
	if (c == '\f' || c == '\r')
		return (1);
	return (0);
}
