#include "lib_main.h"

t_list_dc	*dc_lst_new(void *content)
{
	t_list_dc	*lst_ptr;

	lst_ptr = malloc(sizeof(*lst_ptr));
	if (!lst_ptr)
	{
		return (NULL);
	}
	lst_ptr->next = lst_ptr;
	lst_ptr->content = content;
	lst_ptr->prev = lst_ptr;
	return (lst_ptr);
}
