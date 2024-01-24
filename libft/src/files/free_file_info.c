#include "lib_main.h"

void	free_file_info_ptr(t_file_info *file_info)
{
	free_file_info(*file_info);
	free(file_info);
}

void	free_file_info(t_file_info file_info)
{
	free(file_info.cols);
}
