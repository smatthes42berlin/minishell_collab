#include "lib_main.h"

void	d_lst_iter_node(t_list_d *lst, void (*f)(void *))
{
	t_list_d	*current;

	if (!lst)
		return ;
	f(lst);
	current = lst->next;
	while (current)
	{
		f(current);
		current = current->next;
	}
}
