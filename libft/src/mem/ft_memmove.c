#include "lib_main.h"

static void	handle_critical_overlap(unsigned char *dest_u, unsigned char *src_u,
				size_t n);

static void	handle_standard_case(unsigned char *dest_u, unsigned char *src_u,
				size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*src_u;
	unsigned char	*dest_u;

	if (dest == NULL && src == NULL)
		return (dest);
	src_u = (unsigned char *)src;
	dest_u = (unsigned char *)dest;
	if (src_u < dest_u && (src_u + n) > dest_u)
		handle_critical_overlap(dest_u, src_u, n);
	else
		handle_standard_case(dest_u, src_u, n);
	return (dest);
}

static void	handle_critical_overlap(unsigned char *dest_u, unsigned char *src_u,
		size_t n)
{
	while (n > 0)
	{
		dest_u[n - 1] = src_u[n - 1];
		n--;
	}
}

static void	handle_standard_case(unsigned char *dest_u, unsigned char *src_u,
		size_t n)
{
	size_t	n_cpy;

	n_cpy = n;
	while (n_cpy > 0)
	{
		dest_u[n - n_cpy] = src_u[n - n_cpy];
		n_cpy--;
	}
}
