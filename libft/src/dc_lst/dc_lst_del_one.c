#include "lib_main.h"

void	dc_lst_del_one(t_list_dc *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
	lst = NULL;
}
