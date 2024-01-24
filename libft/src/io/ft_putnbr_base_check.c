#include "lib_main.h"

size_t	ft_putnbr_base_check(const char *base, t_base_info *base_info)
{
	base_info->base_len = ft_strlen(base);
	base_info->base = (char *)base;
	if (base_info->base_len <= 1)
		return (0);
	if (ft_str_cont_chars(base_info->base, "+-"))
		return (0);
	if (ft_str_cont_duplic(base_info->base))
		return (0);
	return (1);
}
