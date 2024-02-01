#include "lib_main.h"

int	d_lst_size(t_list_d *lst)
{
	int			size;

	size = 0;
	if (lst == NULL)
		return (size);
	size++;
	while (lst->next)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
