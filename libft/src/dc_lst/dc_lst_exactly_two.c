#include "lib_main.h"

int	dc_lst_exactly_two(t_list_dc *lst_ptr)
{
	if (!lst_ptr)
		return (0);
	if (lst_ptr->next->next == lst_ptr)
		return (1);
	return (0);
}
