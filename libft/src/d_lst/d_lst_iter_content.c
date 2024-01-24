#include "lib_main.h"

void	d_lst_iter_content(t_list_d *lst, void (*f)(void *))
{
	t_list_d	*current;

	if (!lst)
		return ;
	f(lst->content);
	current = lst->next;
	while (current)
	{
		f(current->content);
		current = current->next;
	}
}
