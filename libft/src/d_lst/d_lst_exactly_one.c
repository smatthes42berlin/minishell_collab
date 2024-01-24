#include "lib_main.h"

int	d_lst_exactly_one(t_list_d *lst_ptr)
{
	if (!lst_ptr)
		return (0);
	if (!lst_ptr->next)
		return (1);
	return (0);
}
