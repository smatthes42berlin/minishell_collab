/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2023/09/03 08:01:38 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
