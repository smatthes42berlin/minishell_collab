#include "lib_main.h"

void	dc_lst_print_one_str_short(void *lst_ptr_void)
{
	t_list_dc	*lst_ptr;

	if (!lst_ptr_void)
		return ;
	lst_ptr = (t_list_dc *)lst_ptr_void;
	ft_printf("%s\n", lst_ptr->content);
	dc_lst_print_sep();
	return ;
}
