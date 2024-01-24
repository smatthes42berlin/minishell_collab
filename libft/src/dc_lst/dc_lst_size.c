#include "lib_main.h"

int	dc_lst_size(t_list_dc *lst)
{
	int			size;
	t_list_dc	*head;

	size = 0;
	head = lst;
	if (lst == NULL)
		return (size);
	size++;
	lst = lst->next;
	while (head != lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
