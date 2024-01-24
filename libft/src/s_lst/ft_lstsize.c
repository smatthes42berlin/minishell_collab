#include "lib_main.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

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
