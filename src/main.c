/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:07:51 by smatthes          #+#    #+#             */
/*   Updated: 2023/11/18 13:24:27 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// input readonly
// output writeonly
// handle errors exactly like bash
// open first file
// check open successful
// redirect stdin to file
// create pip
// fork 1
// when in child1
// redirect stdout to pipe
// close pipes
// run first command
// fork again
// when in child
// redirect stdout to file
// redirect stdin to pipe
// run cmd
// in parent wait for both processes
// additionally, check with path variable if executables exists with access
// also check for error codes
// truncate outfile
// undefined behaviour when same filename

// protect wait pid (could return -1)

//  ./pipex infile "grep a1" "wc -w" outfile

// error code 1 -> no such file or directory
// error code 127 -> command not found

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex_data	data;

	if (handle_args(&data, argc, argv, envp) == -1)
		exit(1);
	if (pipe(data.fd_pipe) == -1)
		clean_exit_error(&data, 1, "");
	data.child_1_pid = fork();
	if (data.child_1_pid == -1)
		clean_exit_error(&data, 1, "");
	if (data.child_1_pid == 0)
		process_cmd1(&data);
	else
	{
		data.child_2_pid = fork();
		if (data.child_2_pid == -1)
			clean_exit_error(&data, 1, "");
		if (data.child_2_pid == 0)
			process_cmd2(&data);
		else
			process_main(&data);
	}
	return (0);
}
