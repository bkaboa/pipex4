/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:40:17 by czang             #+#    #+#             */
/*   Updated: 2022/06/05 15:46:05 by czang            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <errno.h>

/*
 *
 ******************************	define		***
 */
# define ERR_INPUT		"Invalid number of arguments.\n"
# define ERR_CMD		" : Command not found\n"
# define ERR_PIPE		"error with pipe occured\n"
# define ERR_FORK		"FORK: "
# define SPLIT_ERROR	"split error in path\n"
# define PERM_DENIED	" : permission denied\n"
# define FILE_2			" : no such file or permission denied\n"
# define ERR_PATH		"path error\n"
# define NO_ERRNO		0
# define MAX_ERRNO		3

/*
 *
 ******************************	structure	***
 */

static const struct {
	int		code;
	char	*msg;
} s_err[] = {
	{0, NO_ERRNO},
	{1, PERM_DENIED},
	{2, ERR_CMD},
	{3, FILE_2},
};

typedef struct s_pipex
{
	pid_t	id_process;
	pid_t	id_process2;

	int		pipe[2];

	int		infile;
	int		outfile;

	char	**path;
	char	**comd_arg;
	char	*comd_path;
}t_pipex;

typedef struct s_arg
{
	short	ac;
	char	**av;
	char	**env;
}t_arg;

/*
 *
 ******************************	parse_pipex	***
 */
bool	print_error(char *err);
bool	parse_pipex(t_arg arg);
bool	print_err(char *err);

/*
 *
 ******************************	free		***
 */
void	free_main_pid(t_pipex *pipex);
void	free_child_pid(t_pipex *pipex);

/*
 *
 ******************************	fork		***
 */
int		ft_fork(t_pipex pipex, t_arg arg);

/*
 *
 ******************************	small_utils	***
 */
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_strdup(const char *s1);
bool	ft_strncmp(const char *s1, const char *s2, int len);
int		found_occur(char *s, char set);

/*
 *
 ******************************	split		***
 */
char	**ft_split(char *s, char set);
#endif
