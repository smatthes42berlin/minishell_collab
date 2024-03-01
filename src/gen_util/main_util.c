#include "minishell.h"

bool	no_input(t_main_data *main_data)
{
	if (ft_strlen(main_data->cli_input) == 0
		|| str_only_spaces(main_data->cli_input))
	{
		return (true);
	}
	return (false);
}

int	check_num_args(int argc, char *argv[])
{
	if (argc > 1)
	{
		printf("Error: program '%s' doesn't take any arguments!", argv[0]);
		return (1);
	}
	return (0);
}

int	reset_main_data(t_main_data *main_data, bool reset_env)
{
	main_data->ast = NULL;
	main_data->cli_input = NULL;
	main_data->token_list = NULL;
	if (reset_env)
		main_data->env_vars = NULL;
	return (0);
}

t_main_data	*get_main_data(void)
{
	static t_main_data	data = {NULL, NULL, NULL, NULL, 0};

	return (&data);
}

int	read_line(t_main_data *main_data)
{
	main_data->num_lines++;
	main_data->cli_input = readline("cli>");
	// main_data->cli_input = ft_strdup("$empty $empty $empty 123");
	return (0);
}

bool	token_lst_is_empty(t_main_data *main_data)
{
	return (!main_data->token_list);
}
