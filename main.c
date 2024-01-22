/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:02:42 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/22 20:25:48 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * main function and entry point into shell
 * first initialise the main_data structure to mostly NULL

	* then set up all the environment variables coming from main parameter envp and determined via system calls
 * then listen to line input in infinite loop
 * when line entered
 * tokenise the line
 * parse the token list
	* check,if calls are in builts that change main process and must thus be called inside of it
	* execute the ast
 * @param main_data data structure,
	that contains all the necessary data for the shell and gets passed around
*/
int	main(void)
{
	executor();
	return (0);
}
