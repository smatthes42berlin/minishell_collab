#include "./lib_main.h"

int	free_char_variadic_code(int code, int num, ...)
{
	va_list	args;
	char	*next_str;
	int		i;

	if (num <= 0)
		return (0);
	va_start(args, num);
	i = 0;
	while (i < num)
	{
		next_str = va_arg(args, char *);
		free(next_str);
		i++;
	}
	va_end(args);
	return (code);
}
