#include "lib_main.h"

static void	get_res(const char *nptr, t_base_info base_info, long *res);

ssize_t	ft_atoi_base_l(const char *nptr, const char *base)
{
	long		sign;
	long		res;
	t_base_info	base_info;
	int			i;

	i = 0;
	sign = 1;
	res = 0;
	if (!ft_putnbr_base_check(base, &base_info))
		return (0);
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	get_res(&nptr[i], base_info, &res);
	return (res * sign);
}

static void	get_res(const char *nptr, t_base_info base_info, long *res)
{
	int	i;
	int	base_index;

	i = 0;
	base_index = ft_str_chr_index(base_info.base, nptr[i]);
	while (base_index >= 0 && nptr[i])
	{
		*res = *res * base_info.base_len + base_index;
		i++;
		base_index = ft_str_chr_index(base_info.base, nptr[i]);
	}
}
