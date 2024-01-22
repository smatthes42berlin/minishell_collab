/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:44:14 by rkost             #+#    #+#             */
/*   Updated: 2024/01/22 18:49:48 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Using the funktion for safe malloc
 * 
 * @param bytes 
 * @return void* 
 */
void	*malloc_handler(size_t bytes)
{
	void    *ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_code_handler(errno, "ERR-malloc", " ", " ");
	return (ret);
}