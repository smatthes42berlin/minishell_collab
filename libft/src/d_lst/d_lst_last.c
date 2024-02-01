#include "lib_main.h"

t_list_d	*d_lst_last(t_list_d *lst)
{
	t_list_d	*last;

	if (lst == NULL)
		return (NULL);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}
