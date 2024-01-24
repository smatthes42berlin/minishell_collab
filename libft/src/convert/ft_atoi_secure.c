#include "lib_main.h"

static int	ft_strlen_1_to_9(const char *int_str);
static int	handle_to_many_dig(const char *nptr, int sign, long *res);

int	ft_atoi_secure(const char *nptr)
{
	int		sign;
	long	res;
	int		i;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	if (!handle_to_many_dig(&nptr[i], sign, &res))
		return (res);
	while (ft_isdigit(nptr[i]) != 0)
		res = res * 10 + nptr[i++] - '0';
	res = res * sign;
	if (res > INT_MAX)
		return (INT_MAX);
	if (res < INT_MIN)
		return (INT_MIN);
	return (res);
}

static int	handle_to_many_dig(const char *nptr, int sign, long *res)
{
	int	len;

	len = ft_strlen_1_to_9(nptr);
	if (len > 11 && sign > 0)
	{
		*res = INT_MAX;
		return (0);
	}
	if (len > 11 && sign < 0)
	{
		*res = INT_MIN;
		return (0);
	}
	return (1);
}

static int	ft_strlen_1_to_9(const char *int_str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!ft_isdigit(int_str[i]))
		return (0);
	while (int_str[i])
	{
		if (!ft_isdigit(int_str[i]))
			return (0);
		if (ft_isdigit(int_str[i]) && int_str[i] != '0')
			break ;
		i++;
	}
	while (int_str[i] && ft_isdigit(int_str[i]))
	{
		i++;
		len++;
	}
	return (len);
}
