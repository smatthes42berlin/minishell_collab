#include "minishell.h"

static	void	set_env(t_main_data *data, char *env_var);
static	void	read_set_exitcode(char *env_var);

int	env_add_clr(t_main_data *data, char *env_var)
{
	set_env(data, env_var);
	read_set_exitcode(env_var);
	if (ft_strncmp(env_var, EXIT, ft_strlen(EXIT)) == 0)
	{
		return (-1);
	}
	return (0);
}

static	void	set_env(t_main_data *data, char *env_var)
{
	if (data->ast->type != PIPE)
	{
		if (ft_strncmp(env_var, ADD_ENV, ft_strlen(ADD_ENV)) == 0)
			env_set_var(data, env_var + ft_strlen(ADD_ENV));
		else if (ft_strncmp(env_var, CLR_ENV, ft_strlen(CLR_ENV)) == 0)
			env_del_var(data, env_var + ft_strlen(CLR_ENV));
		else if (ft_strncmp(env_var, ADD_CD, ft_strlen(ADD_CD)) == 0)
		{
			if (chdir(env_var + ft_strlen(ADD_CD) + 4) < 0)
				throw_error_custom((t_error_ms){errno, EPART_EXECUTOR,
					EFUNC_CHDIR, "function \"env_add_clr\""});
		}
	}
	return ;
}

static	void	read_set_exitcode(char *env_var)
{
	char	*str_err_msg;

	if (ft_strncmp(env_var, EXIT_CODE, ft_strlen(EXIT_CODE)) == 0)
	{
		if (ft_strchr(env_var, '_') != NULL)
		{
			str_err_msg = (ft_strchr(env_var, '_')
					+ ft_strlen("_MSG="));
			ft_printf_fd(2, "%s\n", str_err_msg);
		}
	}
}
