#include "lib_main.h"

void	d_lst_add_back(t_list_d **lst, t_list_d *new)
{
	t_list_d	*last;

	if (!new)
		return ;
	last = d_lst_last(*lst);
	if (!last)
	{
		*lst = new;
		new->next = NULL;
		new->prev = NULL;
		return ;
	}
	new->prev = last;
	new->next = NULL;
	last->next = new;
}
