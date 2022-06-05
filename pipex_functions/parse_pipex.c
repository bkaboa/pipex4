/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:39:20 by czang             #+#    #+#             */
/*   Updated: 2022/06/05 16:06:49 by czang            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

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
	*env = *env - 5;
	return (true);
}

static void	close_and_wait(t_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
}

static bool	open_files(t_pipex *pipex, t_arg arg)
{
	pipex->outfile = \
		open((arg.av)[arg.ac], O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (pipex->outfile < 0)
	{
		close(pipex->outfile);
		errno = 1;
		return (print_err((arg.av)[arg.ac]));
	}
	pipex->infile = open((arg.av)[1], O_RDONLY);
	if (pipex->infile < 0)
	{
		close(pipex->infile);
		errno = 3;
		print_err((arg.av)[1]);
	}
	errno = 0;
	return (true);
}

bool	parse_pipex(t_arg arg)
{
	t_pipex	pipex;

	if (arg.ac != 4)
		return (print_error(ERR_INPUT));
	if (open_files(&pipex, arg) == false)
		return (false);
	pipe(pipex.pipe);
	if (errno)
		return (print_error(ERR_PIPE));
	if (find_path(&pipex, arg.env) == false)
		return (print_error(ERR_PATH));
	if (ft_fork(pipex, arg) == false)
	{
		free_main_pid(&pipex);
		return (false);
	}
	free_main_pid(&pipex);
	close_and_wait(&pipex);
	return (true);
}
