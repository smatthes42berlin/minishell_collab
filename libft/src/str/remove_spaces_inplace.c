#include "lib_main.h"

static int	move_all_by_one(char **str, int i);

int	remove_spaces_inplace(char **str)
{
	int	i;

	i = 0;
	if (!*str)
		return (0);
	while ((*str)[i])
	{
		if (ft_isspace((*str)[i]))
			move_all_by_one(str, i);
		i++;
	}
	return (0);
}

static int	move_all_by_one(char **str, int i)
{
	int	j;

	j = 0;
	while ((*str)[i + j + 1])
	{
		(*str)[i + j] = (*str)[i + j + 1];
		j++;
	}
	return (0);
}
