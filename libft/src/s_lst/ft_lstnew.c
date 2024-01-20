#include "lib_main.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst_ptr;

	lst_ptr = malloc(sizeof(*lst_ptr));
	if (!lst_ptr)
	{
		return (NULL);
	}
	lst_ptr->next = NULL;
	lst_ptr->content = content;
	return (lst_ptr);
}
