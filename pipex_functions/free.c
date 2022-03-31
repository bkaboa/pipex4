/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:40:44 by czang             #+#    #+#             */
/*   Updated: 2022/03/31 21:40:46 by czang            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
