#include "../Includes/pipex.h"

bool	print_error(char *err)
{
	if (errno)
	{
		perror(err);
		printf("\n\n%d\n\n", errno);
		strerror(errno);
	}
	else
		write(2, err, ft_strlen(err));
	printf("\n\n%d\n\n", errno);
	return (false);
}

static bool	find_path(t_pipex *pipex, char **env)
{
	size_t	i;

	i = 0;
	while (ft_strncmp(*env, "PATH", 4) == false)
		env++;
	*env = *env + 5;
	pipex->path = ft_split(*env, ':');
	if (!pipex->path)
		return (false);
	while (pipex->path[i])
	{
		pipex->path[i] = ft_strjoin(pipex->path[i], "/");
		i++;
	}
	return (true);
}

bool    parse_pipex(t_arg arg)
{
	t_pipex pipex;

    if (arg.ac != 4)
		return (print_error(ERR_INPUT));
	pipex.infile = open((arg.av)[1], O_RDONLY);
	if (pipex.infile < 0)
		return (print_error((arg.av)[1]));
	pipex.outfile = open((arg.av)[arg.ac], O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (pipex.outfile < 0)
		return (print_error((arg.av)[arg.ac]));
	pipe(pipex.pipe);
	if (errno)
		return (print_error(ERR_PIPE));
	if (find_path(&pipex, arg.env) == false)
		return (print_error(ERR_PATH));
	if (ft_fork(pipex, arg) == false)
		return (false);
	return (true);
}
