#include "lib_main.h"

static void	swap_2(t_list_d *head);
static void	swap_3(t_list_d *head);

t_list_d	*dc_lst_swap(t_list_d **lst)
{
	t_list_d	*head;

	head = *lst;
	*lst = head->next;
	if (!lst || !head)
		return (NULL);
	if (dc_lst_exactly_one(head))
		return (head);
	if (dc_lst_exactly_two(head))
		swap_2(head);
	else
		swap_3(head);
	return (*lst);
}

static void	swap_2(t_list_d *head)
{
	t_list_d	*second;

	second = head->next;
	head->next = second;
	head->prev = second;
	second->next = head;
	second->prev = head;
}

static void	swap_3(t_list_d *head)
{
	t_list_d	*second;

	second = head->next;
	head->next = second->next;
	second->prev = head->prev;
	second->next->prev = head;
	head->prev->next = second;
	head->prev = second;
	second->next = head;
}
