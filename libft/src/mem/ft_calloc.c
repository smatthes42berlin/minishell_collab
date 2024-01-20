#include "lib_main.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	long	num_bytes;
	void	*new_mem;

	num_bytes = (long)nmemb * (long)size;
	if (num_bytes > (long)INT_MAX)
		return (NULL);
	new_mem = malloc(num_bytes);
	if (!new_mem)
		return (NULL);
	ft_memset(new_mem, '\0', num_bytes);
	return (new_mem);
}
