#include "lib_main.h"

void	dc_lst_print_one_int_short(void *lst_ptr_void)
{
	t_list_d	*lst_ptr;

	if (!lst_ptr_void)
		return ;
	lst_ptr = (t_list_d *)lst_ptr_void;
	ft_printf("%d\n", *((int *)lst_ptr->content));
	dc_lst_print_sep();
	return ;
}
