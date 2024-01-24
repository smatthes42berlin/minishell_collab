#include "lib_main.h"

void	dc_lst_add_front(t_list_d **lst, t_list_d *new)
{
	dc_lst_add_back(lst, new);
	*lst = new;
}
