/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_num_substr_sq.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 09:52:03 by smatthes          #+#    #+#             */
/*   Updated: 2023/11/18 14:20:26 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib_main.h"
#include <stdio.h>

static int	inside_single_quotes(char const *s, int *i, size_t *num_substr);

size_t	ft_split_num_substr_sq(char const *s, char c)
{
	size_t	state;
	size_t	num_substr;
	int		i;

	state = 0;
	num_substr = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' && ((i == 0) || s[i - 1] == c))
			inside_single_quotes(s, &i, &num_substr);
		else
		{
			if (state == 0 && s[i] != c)
			{
				state = 1;
				num_substr++;
			}
			if (state == 1 && s[i] == c)
				state = 0;
		}
	}
	return (num_substr);
}

static int	inside_single_quotes(char const *s, int *i, size_t *num_substr)
{
	(*i)++;
	if (s[*i] == '\'')
		return (0);
	(*num_substr)++;
	while (s[*i] != '\0' && s[*i] != '\'')
	{
		(*i)++;
	}
	if (s[*i] == '\0')
	{
		(*i)--;
		return (1);
	}
	return (0);
}
