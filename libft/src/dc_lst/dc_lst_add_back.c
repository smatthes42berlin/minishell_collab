#include "lib_main.h"

void	dc_lst_add_back(t_list_d **lst, t_list_d *new)
{
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		new->next = *lst;
		new->prev = (*lst)->prev;
		(*lst)->prev->next = new;
		(*lst)->prev = new;
	}
}
