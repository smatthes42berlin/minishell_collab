#include "lib_main.h"

void	dc_lst_iter_node(t_list_dc *lst, void (*f)(void *))
{
	t_list_dc	*head;
	t_list_dc	*current;

	if (!lst)
		return ;
	head = lst;
	f(head);
	current = lst->next;
	while (head != current)
	{
		f(current);
		current = current->next;
	}
}
