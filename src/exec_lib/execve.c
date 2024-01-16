/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:04:34 by rkost             #+#    #+#             */
/*   Updated: 2024/01/16 16:45:46 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	execve_error_handler_1(int error_code);
// static void	execve_error_handler_2(int error_code);

/**
 * @brief using the execve function 
 * 
 * @param exec -- struct for execve
 */
void	execve_handler(t_node_exec *exec)
{	
	if (access_handler(exec->file_path, FILE_EXECUTABLE) == 0)
	{
		if (execve(exec->file_path, exec->argv, exec->env) == -1)
		{
			error_code_handler(errno, "ERR-execve", exec->file_path, " ");
			exit(EXIT_FAILURE);
		}
	}
	else
		printf("ERR-execve: (access-Error) No executable file path"
			"please check the path!");
}

/** ---------------------------- old error handling -------------
 


static execve_error_handler (int error_code, )

// 
//  * @brief Errorhandling for 'execve' function.
//  * Because norminette accept max. 25 lines. 
//  * -> split in 2 function 
//  * 
//  * @param error_code 
//  
static void	execve_error_handler_1(int error_code)
{
	if (E2BIG == error_code)
		printf("E2BIG ERR-execve: %s\n", strerror(error_code));
	else if (EACCES == error_code)
		printf("EACCES ERR-execve: %s\n", strerror(error_code));
	else if (EAGAIN == error_code)
		printf("EAGAIN ERR-execve: %s\n", strerror(error_code));
	else if (EFAULT == error_code)
		printf("EFAULT ERR-execve: %s\n", strerror(error_code));
	else if (EINVAL == error_code)
		printf("EINVAL ERR-execve: %s\n", strerror(error_code));
	else if (EIO == error_code)
		printf("EIO ERR-execve: %s\n", strerror(error_code));
	else if (EISDIR == error_code)
		printf("EISDIR ERR-execve: %s\n", strerror(error_code));
	else if (EFAULT == error_code)
		printf("EFAULT ERR-execve: %s\n", strerror(error_code));
	else if (ELIBBAD == error_code)
		printf("ELIBBAD ERR-execve: %s\n", strerror(error_code));
	else if (ELOOP == error_code)
		printf("ELOOP ERR-execve: %s\n", strerror(error_code));
	else if (EMFILE == error_code)
		printf("EMFILE ERR-execve: %s\n", strerror(error_code));
	else
		execve_error_handler_2(error_code);
}

//
//  * @brief 'execve_error_handler' -> split in 2 function.
//  * Because norminette accept max. 25 lines.
//  * 
//  * @param error_code 
//  
static void	execve_error_handler_2(int error_code)
{
	if (ENAMETOOLONG == error_code)
		printf("ENAMETOOLONG ERR-execve: %s\n", strerror(error_code));
	else if (ENFILE == error_code)
		printf("ENFILE ERR-execve: %s\n", strerror(error_code));
	else if (ENOENT == error_code)
		printf("ENOENT ERR-execve: %s\n", strerror(error_code));
	else if (ENOEXEC == error_code)
		printf("ENOEXEC ERR-execve: %s\n", strerror(error_code));
	else if (ENOTDIR == error_code)
		printf("ENOTDIR ERR-execve: %s\n", strerror(error_code));
	else if (EPERM == error_code)
		printf("EPERM ERR-execve: %s\n", strerror(error_code));
	else if (ETXTBSY == error_code)
		printf("ETXTBSY ERR-execve : %s\n", strerror(error_code));
	else
		printf("UNKNOWN ERR-execve: %s\n", strerror(error_code));
}

*/