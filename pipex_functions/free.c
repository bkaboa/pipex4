
#include "../Includes/pipex.h"

static void	free_db_pointer(void **pointer)
{
	int		i;

	i = 0;
	while (pointer[i])
		free(pointer[i++]);
	free(pointer);
}

void	free_main_pid(t_pipex *pipex)
{
	free_db_pointer((void **)pipex->path);
}

void	free_child_pid(t_pipex *pipex)
{
	free_db_pointer((void **)pipex->comd_arg);
	free(pipex->comd_path);
}
