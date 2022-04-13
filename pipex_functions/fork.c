/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:39:21 by czang             #+#    #+#             */
/*   Updated: 2022/03/31 22:17:06 by czang            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

static char	*find_comd_path(char **path, char *comd)
{
	char	*comd_path;

	if (comd[0] == '\0')
		return (NULL);
	while (*path)
	{
		comd_path = ft_strjoin(*path, comd);
		if (access(comd_path, 0) == 0)
			return (comd_path);
		free(comd_path);
		path++;
	}
	print_error(comd);
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
	if (!pipex.comd_path)
	{
		free_child_pid(&pipex);
		exit(1);
	}
	execve(pipex.comd_path, pipex.comd_arg, arg.env);
}

static void	child2(t_pipex pipex, t_arg arg)
{
	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[1]);
	dup2(pipex.outfile, 1);
	close(pipex.outfile);
	pipex.comd_arg = ft_split(arg.av[3], ' ');
	pipex.comd_path = find_comd_path(pipex.path, pipex.comd_arg[0]);
	if (!pipex.comd_path)
	{
		free_child_pid(&pipex);
		exit(1);
	}
	execve(pipex.comd_path, pipex.comd_arg, arg.env);
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
		return (print_error(ERR_FORK));
	if (pipex.id_process2 == 0)
		child2(pipex, arg);
	return (true);
}
