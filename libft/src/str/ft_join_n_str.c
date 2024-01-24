#include "lib_main.h"

static int	free_va_arg(va_list args, int code);

int	ft_join_n_str(char **res, int num, ...)
{
	va_list	args;
	char	*next_str;
	char	*tmp;
	int		i;
	int		status;

	va_start(args, num);
	if (num <= 0)
		return (free_va_arg(args, 1));
	*res = NULL;
	i = 0;
	while (i < num)
	{
		next_str = va_arg(args, char *);
		tmp = *res;
		status = ft_str_n_join_int(tmp, next_str, 0, res);
		free(tmp);
		if (status == -1)
			return (free_va_arg(args, -1));
		i++;
	}
	return (free_va_arg(args, 1));
}

static int	free_va_arg(va_list args, int code)
{
	va_end(args);
	return (code);
}
