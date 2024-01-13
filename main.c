/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:02:42 by smatthes          #+#    #+#             */
/*   Updated: 2024/01/13 13:26:08 by smatthes         ###   ########.fr       */
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
	t_main_data main_data;

	// init_main_data(&main_data);
	// - set up and handle environment
	while (1)
	{
		// watch out for eof and possbile return of null
		main_data.cli_input = readline("cli>");
		if (tokenise(main_data) == -1)
			return (1);
		// if (parse(main_data) == -1)
		// 	return (2);
		// - (Check if inbuilts that change main process, e.g. cd)
		// if (execute(main_data) == -1)
		// 	return (3);
	}
	return (0);
}