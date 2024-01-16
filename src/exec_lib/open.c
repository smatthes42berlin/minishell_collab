/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:09:12 by rene              #+#    #+#             */
/*   Updated: 2024/01/15 22:27:34 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void open_handler(const char *path, t_en_open_mode mode)
{
    int result;
    
    if(safe_access_handler(&path,FILE_EXISTS) != 0)
        result = open(path, mode | O_CREAT, S_IRWXU);
    else
        result = open(path, mode);
    if (result)    
}