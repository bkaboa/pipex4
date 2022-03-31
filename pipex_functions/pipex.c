/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:40:51 by czang             #+#    #+#             */
/*   Updated: 2022/03/31 22:16:24 by czang            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;

	argc -= 1;
	arg.ac = argc;
	arg.av = argv;
	arg.env = envp;
	if (parse_pipex(arg) == false)
		return (1);
	return (0);
}
