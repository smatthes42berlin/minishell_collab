#include "lib_main.h"

static void	print_format_cont(char *label, char *cont);
static void	print_format_ptr(char *label, t_list_d *ptr);

void	dc_lst_print_one_str_long(void *lst_ptr_void)
{
	t_list_d	*lst_ptr;

	if (!lst_ptr_void)
		return ;
	lst_ptr = (t_list_d *)lst_ptr_void;
	print_format_ptr("prev ptr:", lst_ptr->prev);
	print_format_cont("prev cont:", lst_ptr->prev->content);
	print_format_ptr("own ptr:", lst_ptr);
	print_format_cont("own cont:", lst_ptr->content);
	print_format_ptr("next ptr:", lst_ptr->next);
	print_format_cont("next cont:", lst_ptr->next->content);
	dc_lst_print_sep();
	return ;
}

static void	print_format_cont(char *label, char *cont)
{
	ft_printf("%s\t%s\n", label, cont);
}

static void	print_format_ptr(char *label, t_list_d *ptr)
{
	ft_printf("%s\t%p\n", label, ptr);
}
