#include "lib_main.h"

void	d_lst_del_one(t_list_d *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
	lst = NULL;
}
