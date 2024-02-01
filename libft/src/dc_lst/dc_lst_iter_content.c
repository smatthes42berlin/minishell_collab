#include "lib_main.h"

void	dc_lst_iter_content(t_list_d *lst, void (*f)(void *))
{
	t_list_d	*head;
	t_list_d	*current;

	if (!lst)
		return ;
	head = lst;
	f(head->content);
	current = lst->next;
	while (head != current)
	{
		f(current->content);
		current = current->next;
	}
}
