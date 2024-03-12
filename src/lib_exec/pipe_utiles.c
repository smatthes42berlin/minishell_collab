#include "minishell.h"

int	use_dup2(int oldfd, int newfd, char *error_msg)
{
	int	ret;

	ret = 0;
	if (dup2(oldfd, newfd) < 0)
	{
		throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_DUP2,
			error_msg});
		ret = -1;
	}
	return (ret);
}

int	use_close(int pipefd, char *error_msg)
{
	int	ret;

	ret = 0;
	if (close(pipefd) < 0)
	{
		ret = throw_error_custom((t_error_ms){errno, EPART_EXECUTOR, EFUNC_DUP2,
				error_msg});
		ret = -1;
	}
	return (ret);
}
