/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:12:59 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/14 10:18:05 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenise(t_main_data *main_data)
{
	char	*cur_pos;

	cur_pos = main_data->cli_input;
	while (*cur_pos)
	{
		printf("1\n");
		skip_ws(&cur_pos);
		if (get_token(&cur_pos, main_data))
			return (printf("ERROR\n"));
	}
	return (1);
}

int	get_token(char **cur_pos, t_main_data *main_data)
{
	t_token	*new_token;

	new_token = create_token();
	if (!new_token)
		return (printf("Token creation Error!\n"));
	if (append_token_list(main_data, new_token))
		return (printf("Error appending Token to list!\n"));
	if (identify_token(cur_pos, new_token))
		return (1);
	return (0);
}
