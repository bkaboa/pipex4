/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:13:54 by czang             #+#    #+#             */
/*   Updated: 2022/06/05 15:46:04 by czang            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

bool	print_error(char *err)
{
	if (errno)
	{
		perror(err);
		strerror(errno);
	}
	else
		write(2, err, ft_strlen(err));
	return (false);
}

bool	print_err(char *err)
{
	u_int8_t	i;

	i = 1;
	if (err)
		write(2, err, ft_strlen(err));
	while (i <= MAX_ERRNO && i != errno)
		++i;
	if (errno == s_err[i].code)
		write(2, s_err[i].msg, ft_strlen(s_err[i].msg));
	return (false);
}
