#include "minishell.h"

// static const char	*access_mode_to_str(enum e_access_mode mode);

/**
 * @brief using for checking the right of the given path
 * 
 * @param path
 * @param mode checking mode for [FILE_EXISTS]; [FILE_READABLE]; 
 * 								[FILE_WRITABLE]; [FILE_EXECUTABLE]
 * @return (int [0] 	- File was exapted with this mode);
 * 				[-1]	- error return ;
 */
int	access_handler(const char *path, enum e_access_mode mode, int debug_mode)
{
	int	result;

	result = -1;
	if (FILE_EXISTS == mode || FILE_READABLE == mode || FILE_WRITABLE == mode
		|| FILE_EXECUTABLE == mode)
	{
		result = access(path, mode);
		if (result < 0 && debug_mode)
			throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_ACCESS,
				"function \"access_handler\""});
	}
	else
	{
		printf("ERROR 'access' - Wrong Mode given\n");
		return (result);
	}
	return (result);
}

// /**
//  * @brief return the given enum t_access_mode to a String
//  * 
//  * @param mode mode for [FILE_EXISTS]; [FILE_READABLE];
//  * 				[FILE_WRITABLE]; [FILE_EXECUTABLE]
//  * @return (const char* "FILE_EXISTS"); "FILE_READABLE"; 
//  * 			"FILE_WRITABLE"; "FILE_EXECUTABLE"
//  */
// static const char	*access_mode_to_str(enum e_access_mode mode)
// {
// 	if (mode == FILE_EXISTS)
// 		return ("MODE-FILE_EXISTS");
// 	else if (mode == FILE_READABLE)
// 		return ("MODE-FILE_READABLE");
// 	else if (mode == FILE_WRITABLE)
// 		return ("MODE-FILE_WRITABLE");
// 	else if (mode == FILE_EXECUTABLE)
// 		return ("MODE-FILE_EXECUTABLE");
// 	else
// 		return ("MODE-UNKNOWN_MODE");
// }