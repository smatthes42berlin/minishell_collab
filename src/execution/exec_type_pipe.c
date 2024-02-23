#include "minishell.h"

static int	type_pipe_nested_pid(t_main_data *data, t_node_pipe *pipe_node,
				pid_t main_pid, int *pipefd, bool direction,
				t_pipefd *pipe_struct_main);
void check_open_fd(void);



void test_pipe(t_main_data *data, t_node *node, t_pipefd *pipe_struct)
{
	int		pipefd[2];
	pid_t	cpid;
	pid_t	cpid2;
	t_node_pipe	*pipe_node;
	
	pipe_node = (t_node_pipe *)node;

	pipe(pipefd);

	cpid = fork();
	if (cpid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		navigate_tree_forward(data, pipe_node->left_node, pipe_struct);
	}
	else
	{
		cpid2 = fork();
		if (cpid2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			navigate_tree_forward(data, pipe_node->right_node, pipe_struct);
		}
		else
		{
			close(pipefd[0]);
			close(pipefd[1]);
			waitpid(cpid2, NULL, 0);
			waitpid(cpid, NULL, 0);
			printf("DONE\n");
		}
	}
}















int	type_pipe(t_main_data *data, t_node *node, t_pipefd *pipe_struct)
{
	t_node_pipe	*pipe_node;
	int			pipefd[2];
	pid_t		main_pid;
	int			ret;

	ret = 0;
	pipe_node = (t_node_pipe *)node;
	print_debugging_info_executer(INT_DEBUG, 6, NULL);
	pipe_handler(pipefd, "function \"type_pipe\"");
	main_pid = fork_handler("function \"type_pipe\"");
	if (main_pid == 0)
	{
		if (!check_is_inbuilt(data, pipe_node->left_node, pipe_struct, pipefd))
		{
			// close(pipefd[1]);
			// dup2(pipefd[0], STDOUT_FILENO);
			pipe_setting(pipefd, true, NULL, "function \"type pipe\" child");
			navigate_tree_forward(data, pipe_node->left_node, pipe_struct);
		}
	}
	else
	{
		ret = type_pipe_nested_pid(data, pipe_node, main_pid, pipefd, false,
				pipe_struct);
	}

	return (ret);
}

static int	type_pipe_nested_pid(t_main_data *data, t_node_pipe *pipe_node,
		pid_t main_pid, int *pipefd, bool direction, t_pipefd *pipe_struct_main)
{
	pid_t nested_pid;
	int status;
	int ret;

	ret = 0;

	if(direction)
		printf("NOTING");

	// close(pipefd[0]);
	// dup2(pipefd[1], STDIN_FILENO);
	pipe_setting(pipefd, direction, NULL, "function \"type pipe\" parent");
	//check_open_fd();

	//printf("\n\n\n-----------------------------------------------\n\n\n");
	//check_open_fd();
	nested_pid = fork_handler("function \"type_pipe_nested_pid\"");
	if (nested_pid == 0)
	{
		navigate_tree_forward(data, pipe_node->right_node, pipe_struct_main);
	}
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(nested_pid, &status, 0);
		waitpid(main_pid, NULL, 0);

		ret = get_process_exit_code(status);
	}
	return (ret);
}

void check_open_fd(void) 
{
    DIR *dir;
    struct dirent *dp;
    char *endptr;
    long fd;

    // Öffne das Verzeichnis /proc/self/fd, um die offenen Dateideskriptoren zu finden
    dir = opendir("/proc/self/fd");
    if (dir == NULL) {
        perror("opendir");
        //return EXIT_FAILURE;
    }

    // Iteriere durch die Einträge im Verzeichnis
    while ((dp = readdir(dir)) != NULL) 
	{
        // Konvertiere den Namen (der ein Dateideskriptor ist) in eine lange Zahl
        fd = strtol(dp->d_name, &endptr, 10);
        // Überspringe ungültige Einträge (z.B. ".", "..", oder keine Zahlen)
        if (*endptr != '\0') continue;

        printf("Offener Dateideskriptor: %ld\n", fd);
		// if (fd > 1)
		// 	close(fd);
    }

    // Schließe das Verzeichnis
    //closedir(dir);

   // return EXIT_SUCCESS;
}