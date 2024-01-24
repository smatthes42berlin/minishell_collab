#include "lib_main.h"

void	dc_lst_clear(t_list_dc **lst, void (*del)(void *))
{
	t_list_dc	*temp;
	t_list_dc	*current;
	t_list_dc	*head;

	if (!lst || !*lst)
		return ;
	head = *lst;
	current = (*lst)->next;
	while (head != current)
	{
		temp = current;
		current = current->next;
		dc_lst_del_one(temp, del);
	}
	dc_lst_del_one(head, del);
	*lst = NULL;
}
