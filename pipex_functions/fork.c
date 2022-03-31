
#include "../Includes/pipex.h"

static char	*find_comd_path(char **path, char  *comd)
{
	char	*comd_path;

	while (*path)
	{
		comd_path = ft_strjoin(*path, comd);
		if (access(comd_path, 0) == 0)
			return (comd_path);
		free(comd_path);
		path++;
	}
	return (NULL);
}

static void	child1(t_pipex pipex, t_arg arg)
{
	dup2(pipex.pipe[1], 1);
	close(pipex.pipe[0]);
	dup2(pipex.infile, 0);
	close(pipex.infile);
	pipex.comd_arg = ft_split(arg.av[2], ' ');
	pipex.comd_path = find_comd_path(pipex.path, pipex.comd_arg[0]);
	dprintf(2, "\n\n\n %s \n\n\n", pipex.comd_path);
	if (!pipex.comd_path)
	{
		free_child_pid(&pipex);
		print_error(ERR_CMD1);
		exit(1);
	}
	execve(pipex.comd_path, &arg.av[2], arg.env);
}

static void	child2(t_pipex pipex, t_arg arg)
{
	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[1]);
	dup2(pipex.outfile, 1);
	close(pipex.outfile);
	pipex.comd_arg = ft_split(arg.av[3], ' ');
	pipex.comd_path = find_comd_path(pipex.path, pipex.comd_arg[0]);
	dprintf(2, "\n\n\n %s \n\n\n", pipex.comd_path);
	if (!pipex.comd_path)
	{
		free_child_pid(&pipex);
		print_error(ERR_CMD2);
		exit(1);
	}
	dprintf(2, "\n\n\n %s \n\n\n", arg.av[3]);
	dprintf(2, "\n\n\n %d \n\n\n", errno);
	
	execve(pipex.comd_path, &arg.av[3], arg.env);
}

int	ft_fork(t_pipex pipex, t_arg arg)
{
	pipex.id_process = fork();
	if (pipex.id_process == -1)
		return (print_error(ERR_FORK));
	if (pipex.id_process == 0)
		child1(pipex, arg);
	pipex.id_process2 = fork();
	if (pipex.id_process2 == -1)
		return (false);
		//return (print_error(ERR_FORK, pipex.id_process2));
	if (pipex.id_process2 == 0)
		child2(pipex, arg);
	return (true);
}
