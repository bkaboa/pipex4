

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
 ******************************	structure	***
 */
typedef struct s_pipex
{
	pid_t id_process;
	pid_t id_process2;

	int pipe[2];

	int	infile;
	int	outfile;

	char **path;
	char **comd_arg;
	char *comd_path;
}t_pipex;

typedef struct s_arg
{
	short ac;
	char **av;
	char **env;
}t_arg;

/*
 *
 ******************************	define		***
 */
# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_CMD1 "Command 1 not found\n"
# define ERR_CMD2 "Command 2 not found\n"
# define ERR_PIPE "error with pipe occured\n"
# define ERR_FORK "FORK: "
# define SPLIT_ERROR "split error in path\n"
# define ERR_PATH "path_error\n"
# define NO_ERRNO 0

/*
 *
 ******************************	parse_pipex	***
 */
bool	print_error(char *err);
bool    parse_pipex(t_arg arg);

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
int	ft_fork(t_pipex pipex, t_arg arg);

/*
 *
 ******************************	small_utils	***
 */
size_t	ft_strlen(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
bool	ft_strncmp(const char *s1, const char *s2, int len);
int	found_occur(char *s, char set);

/*
 *
 ******************************	split		***
 */
char	**ft_split(char *s, char set);
#endif
