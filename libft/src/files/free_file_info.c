/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:18:26 by smatthes          #+#    #+#             */
/*   Updated: 2023/10/29 13:09:52 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_main.h"

void	free_file_info_ptr(t_file_info *file_info)
{
	free_file_info(*file_info);
	free(file_info);
}

void	free_file_info(t_file_info file_info)
{
	free(file_info.cols);
}
