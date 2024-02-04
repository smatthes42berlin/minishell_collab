#include "minishell.h"

/**
 * @brief Create a node pid list object
 *
 * @param pid a process ID number to creat a new linked list with PID
 * @return t_list*
 */
t_list	*create_node_pid_list(pid_t pid)
{
	t_list	*new_node;
	pid_t	*pid_ptr;

	new_node = malloc(sizeof(t_list));
	pid_ptr = malloc(sizeof(pid_t));
	if (new_node == NULL || pid_ptr == NULL)
	{
		free(new_node);
		free(pid_ptr);
		return (NULL);
	}
	*pid_ptr = pid;
	new_node->content = pid_ptr;
	new_node->next = NULL;
	return (new_node);
}

/**
 * @brief append a Process ID nbr to a given linked list
 *
 * @param head a linked list with Process ID numbers
 * @param pid the Process ID number to add
 */
void	append_node_pid_list(t_list **head, pid_t pid)
{
	t_list	*new_node;
	t_list	*current;

	new_node = create_node_pid_list(pid);
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

/**
 * @brief use for print the list of all generate Process ID during the
 * 				forking processes
 *
 * @param head a linked list with Process ID numbers
 */
void	print_list_pid_list(t_list *head)
{
	t_list	*current;
	pid_t	*pid_ptr;

	current = head;
	printf("PID-LIST IS: ");
	while (current != NULL)
	{
		pid_ptr = (pid_t *)current->content;
		if (pid_ptr != NULL)
		{
			printf("%d ", *pid_ptr);
		}
		current = current->next;
	}
	printf("\n");
}

/**
 * @brief
 *
 * @param head a linked list with Process ID numbers
 */
void	free_list_pid_list(t_list *head)
{
	t_list	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

/**
 * @brief use to wait for all Process ende
 *
 * @param pid_list a linked list with Process ID numbers
 */
void	wait_for_all_processes(t_list *pid_list)
{
	t_list	*current;
	pid_t	*pid_ptr;

	current = pid_list;
	while (current != NULL)
	{
		pid_ptr = (pid_t *)(current->content);
		if (pid_ptr != NULL)
		{
			waitpid(*pid_ptr, NULL, 0);
		}
		current = current->next;
	}
}
