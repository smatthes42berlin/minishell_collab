#include "lib_main.h"

int	dc_lst_exactly_one(t_list_d *lst_ptr)
{
	if (!lst_ptr)
		return (0);
	if (lst_ptr->next == lst_ptr)
		return (1);
	return (0);
}
