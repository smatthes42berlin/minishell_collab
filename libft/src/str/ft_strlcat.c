#include "lib_main.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	s_i;
	size_t	d_i;

	dest_len = 0;
	while (dest_len < size && dst[dest_len])
		dest_len++;
	src_len = ft_strlen(src);
	d_i = dest_len;
	s_i = 0;
	if (size <= dest_len)
		return (src_len + size);
	while (d_i < (size - 1) && src[s_i])
	{
		dst[d_i] = src[s_i];
		d_i++;
		s_i++;
	}
	dst[d_i] = '\0';
	return (src_len + dest_len);
}
