#include "lib_main.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new_node;
	t_list	*prev_node;

	head = NULL;
	if (lst == NULL)
		return (head);
	head = ft_lstnew(f(lst->content));
	lst = lst->next;
	new_node = head;
	while (lst)
	{
		prev_node = new_node;
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&prev_node, new_node);
		lst = lst->next;
	}
	return (head);
}
