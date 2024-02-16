#include "lib_main.h"

t_list_d	*d_lst_pop_current(t_list_d **lst)
{
	int			has_prev;
	int			has_next;
	t_list_d	*to_pop;

	if (!lst || !*lst)
		return (NULL);
	has_prev = (*lst)->prev != NULL;
	has_next = (*lst)->next != NULL;
	to_pop = *lst;
	*lst = NULL;
	if (has_prev)
	{
		to_pop->prev->next = to_pop->next;
	}
	if (has_next)
	{
		to_pop->next->prev = to_pop->prev;
		*lst = to_pop->next;
	}
	to_pop->next = NULL;
	to_pop->prev = NULL;
	return (to_pop);
}
