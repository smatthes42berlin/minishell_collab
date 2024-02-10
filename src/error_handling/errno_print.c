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

/** ---------------------------------- complett error handling 
void error_code_handler(int error_code, const char *msg, const char *mode)
{
    if (0 == error_code)
	    return ;
	else if (E2BIG == error_code)
		printf("E2BIG %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EACCES == error_code)
		printf("EACCES %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EADDRINUSE == error_code)
		printf("EADDRINUSE %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EADDRNOTAVAIL == error_code)
		printf("EADDRNOTAVAIL %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EAFNOSUPPORT == error_code)
		printf("EAFNOSUPPORT %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EAGAIN == error_code)
		printf("EAGAIN %s %s: %s\n", msg, mode, strerror(error_code));    
	else if (EWOULDBLOCK == error_code)
		printf("EWOULDBLOCK %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EALREADY == error_code)
		printf("EALREADY %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EBADE == error_code)
		printf("EBADE %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EBADF == error_code)
		printf("EBADF %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EBADFD == error_code)
		printf("EBADFD %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EBADMSG == error_code)
		printf("EBADMSG %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EBADR == error_code)
		printf("EBADR %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EBADRQC == error_code)
		printf("EBADRQC %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EBADSLT == error_code)
		printf("EBADSLT %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EBUSY == error_code)
		printf("EBUSY %s %s: %s\n", msg, mode, strerror(error_code));
	else if (ECANCELED == error_code)
		printf("ECANCELED %s %s: %s\n", msg, mode, strerror(error_code));
    else if (ECHILD == error_code)
		printf("ECHILD %s %s: %s\n", msg, mode, strerror(error_code));
	else if (ECHRNG == error_code)
		printf("ECHRNG %s %s: %s\n", msg, mode, strerror(error_code));
    else if (ECOMM == error_code)
		printf("ECOMM %s %s: %s\n", msg, mode, strerror(error_code));
	else if (ECONNABORTED == error_code)
		printf("ECONNABORTED %s %s: %s\n", msg, mode, strerror(error_code));
    else if (ECONNREFUSED == error_code)
		printf("ECONNREFUSED %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EDOM == error_code)
		printf("EDOM %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EDQUOT == error_code)
		printf("EDQUOT %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EEXIST == error_code)
		printf("EEXIST %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EFAULT == error_code)
		printf("EFAULT %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EFBIG == error_code)
		printf("EFBIG %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EHOSTDOWN == error_code)
		printf("EHOSTDOWN %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EHOSTUNREACH == error_code)
		printf("EHOSTUNREACH %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EHWPOISON == error_code)
		printf("EHWPOISON %s %s: %s\n", msg, mode, strerror(error_code));       
	else if (EIDRM == error_code)
		printf("EIDRM %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EILSEQ == error_code)
		printf("EILSEQ %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EINPROGRESS == error_code)
		printf("EINPROGRESS %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EINTR == error_code)
		printf("EINTR %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EINVAL == error_code)
		printf("EINVAL %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EIO == error_code)
		printf("EIO %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EISCONN == error_code)
		printf("EISCONN %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EISDIR == error_code)
		printf("EISDIR %s %s: %s\n", msg, mode, strerror(error_code));   
	else if (EISNAM == error_code)
		printf("EISNAM %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EKEYEXPIRED == error_code)
		printf("EKEYEXPIRED %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EKEYREJECTED == error_code)
		printf("EKEYREJECTED %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EKEYREVOKED == error_code)
		printf("EKEYREVOKED %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EL2HLT == error_code)
		printf("EL2HLT %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EL2NSYNC == error_code)
		printf("EL2NSYNC %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EL3HLT == error_code)
		printf("EL3HLT %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EL3RST == error_code)
		printf("EL3RST %s %s: %s\n", msg, mode, strerror(error_code)); 
	else if (ELIBACC == error_code)
		printf("EISNAM %s %s: %s\n", msg, mode, strerror(error_code));
    else if (ELIBBAD == error_code)
		printf("ELIBBAD %s %s: %s\n", msg, mode, strerror(error_code));
	else if (ELIBMAX == error_code)
		printf("ELIBMAX %s %s: %s\n", msg, mode, strerror(error_code));
    else if (ELIBSCN == error_code)
		printf("ELIBSCN %s %s: %s\n", msg, mode, strerror(error_code));
	else if (ELIBEXEC == error_code)
		printf("ELIBEXEC %s %s: %s\n", msg, mode, strerror(error_code));
    else if (ELNRNG == error_code)
		printf("ELNRNG %s %s: %s\n", msg, mode, strerror(error_code));
	else if (ELOOP == error_code)
		printf("ELOOP %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EMEDIUMTYPE == error_code)
		printf("EMEDIUMTYPE %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EMFILE == error_code)
		printf("EMFILE %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EMLINK == error_code)
		printf("EMLINK %s %s: %s\n", msg, mode, strerror(error_code));
	else if (EMSGSIZE == error_code)
		printf("EMSGSIZE %s %s: %s\n", msg, mode, strerror(error_code));
    else if (EMULTIHOP == error_code)
		printf("EMULTIHOP %s %s: %s\n", msg, mode, strerror(error_code));
	else if (ENAMETOOLONG == error_code)
		printf("ENAMETOOLONG %s %s: %s\n", msg, mode, strerror(error_code));
    else if (ENETDOWN == error_code)
		printf("ENETDOWN %s %s: %s\n", msg, mode, strerror(error_code));
	else if (ENETRESET == error_code)
		printf("ENETRESET %s %s: %s\n", msg, mode, strerror(error_code));
    else if (ENETUNREACH == error_code)
		printf("ENETUNREACH %s %s: %s\n", msg, mode, strerror(error_code)); 
	else if (ENFILE == error_code)
		printf("ENFILE %s %s: %s\n", msg, mode, strerror(error_code));
    else if (ENOANO == error_code)
		printf("ENOANO %s %s: %s\n", msg, mode, strerror(error_code));
	else if (ENOBUFS == error_code)
		printf("ENOBUFS %s %s: %s\n", msg, mode, strerror(error_code));
    else if (ENODATA == error_code)
		printf("ENODATA %s %s: %s\n", msg, mode, strerror(error_code));
	else if (ENODEV == error_code)
		printf("ENODEV %s %s: %s\n", msg, mode, strerror(error_code));
    else if (ENOENT == error_code)
		printf("ENOENT %s %s: %s\n", msg, mode, strerror(error_code));
	else if (ENOEXEC == error_code)
		printf("ENOEXEC %s %s: %s\n", msg, mode, strerror(error_code));
    else if (ENOKEY == error_code)
		printf("ENOKEY %s %s: %s\n", msg, mode, strerror(error_code)); 
    
// Some errors are missing 
    
    else 
        printf("UNKNOWN %s %s: %s\n", msg, mode, strerror(error_code));
    
}
*/