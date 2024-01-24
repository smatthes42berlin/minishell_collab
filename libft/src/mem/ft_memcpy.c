#include "lib_main.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_u;
	unsigned char	*src_u;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	dest_u = (unsigned char *)dest;
	src_u = (unsigned char *)src;
	while (i < n)
	{
		dest_u[i] = src_u[i];
		i++;
	}
	return (dest);
}
