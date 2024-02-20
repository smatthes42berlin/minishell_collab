#include "minishell.h"

/** errno - descripten 
 * 
 * errno-typ       | function 
 * ---------------------------------------------
 *  E2BIG           execve 
 *  EACCES          access, execve, open, getcwd
 *  EAGAIN          execve, fork
 *  EBADF           access, open, close
 * 	EBUSY			open
 * 	ECHILD			wait(pid)
 * 	EDQUOT			open, close				
 * 	EEXIST			open
 *  EFAULT          access, execve, open, pipe, getcwd
 * 	EFBIG			open
 * 	EINTR			open, close, wait(pid)
 *  EINVAL          access, execve, open, waitpid, pipe, getcwd
 *  EIO             access, execve, close
 *  EISDIR          execve, open
 *  ELIBBAD         execve
 *  ELOOP           access, execve, open
 *  EMFILE          execve, open, , pipe
 *  ENAMETOOLONG    access, execve, open, getcwd
 *  ENFILE          execve, open, pipe
 * 	ENODEV			open
 *  ENOENT          access, execve, open, getcwd
 *  ENOEXEC         execve
 *  ENOMEM          access, execve, open, fork, getcwd
 * 	ENOSPC			open, close
 * 	ENOSYS			fork
 *  ENOTDIR         access, execve, open
 * 	ENXIO			open
 * 	EOPNOTSUPP		open
 * 	EOVERFLOW		open
 *  EPERM           access, execve, open
 * 	ERESTARTNOINTR	fork
 * 	ERANGE			getcwd
 *  EROFS           access, open
 *  ETXTBSY         access, execve, open
 * 	EWOULDBLOCK		open
 * 
*/
void error_code_handler(int error_code, const char *msg, const char *subj, const char *mode)
{
    if (0 == error_code)
	    return ;
	errno = 0;
	printf("🚫 ➡️ ");
	if (E2BIG == error_code) 
		printf("E2BIG %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
    else if (EACCES == error_code)
		printf("EACCES %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
    else if (EAGAIN == error_code)
		printf("EAGAIN %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (EBADF == error_code)
		printf("EBADF %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (EBUSY == error_code)
		printf("EBUSY %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (ECHILD == error_code)
		printf("ECHILD %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (EDQUOT == error_code)
		printf("EDQUOT %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (EEXIST == error_code)
		printf("EEXIST %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
    else if (EFAULT == error_code)
		printf("EFAULT %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
    else if (EINVAL == error_code)
		printf("EINVAL %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (EIO == error_code)
		printf("EIO %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
    else if (EISDIR == error_code)
		printf("EISDIR %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (ELIBBAD == error_code)
		printf("ELIBBAD %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (ELOOP == error_code)
		printf("ELOOP %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (EMFILE == error_code)
		printf("EMFILE %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
    else if (ENAMETOOLONG == error_code)
		printf("ENAMETOOLONG %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
    else if (ENFILE == error_code)
		printf("ENFILE %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
    else if (ENODEV == error_code)
		printf("ENODEV %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (ENOENT == error_code)
		printf("ENOENT %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
    else if (ENOEXEC == error_code)
		printf("ENOEXEC %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
    else if (ENOMEM == error_code)
		printf("ENOMEM %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
    else if (ENOSPC == error_code)
		printf("ENOSPC %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (ENOSYS == error_code)
		printf("ENOSYS %s %s %s: %s\n", msg, subj, mode, strerror(error_code));	
    else if (ENOTDIR == error_code)
		printf("ENOTDIR %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
    else if (ENXIO == error_code)
		printf("ENXIO %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
    else if (EOPNOTSUPP == error_code)
		printf("EOPNOTSUPP %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
    else if (EOVERFLOW == error_code)
		printf("EOVERFLOW %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (EPERM == error_code)
		printf("EPERM %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	// else if (ERESTARTNOINTR == error_code)
	// 	printf("ERESTARTNOINTR %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (ERANGE == error_code)
		printf("ERANGE %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (EROFS == error_code)
		printf("EROFS %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (ETXTBSY == error_code)
		printf("ETXTBSY %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (EWOULDBLOCK == error_code)
		printf("EWOULDBLOCK %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	else if (1000 == error_code)
		printf("ERROR %s %s %s %s\n", msg, subj, mode, " ");	
    else
	{
        printf("UNKNOWN %s %s %s: %s\n", msg, subj, mode, strerror(error_code));
	}
	//exit(EXIT_FAILURE);   
}
