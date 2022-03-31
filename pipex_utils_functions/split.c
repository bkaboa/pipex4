/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:40:02 by czang             #+#    #+#             */
/*   Updated: 2022/03/31 21:40:04 by czang            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/pipex.h"

static size_t	sentences_size(char *s, char set)
{
	size_t	i;
	size_t	y;

	y = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == set)
		{
			y++;
			while (s[i] == set && s[i])
				i++;
		}
		i++;
	}
	y++;
	return (y);
}

static char	*word(const char *s, char set)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(s);
	while (tmp[i] && tmp[i] != set)
		i++;
	tmp[i] = '\0';
	return (tmp);
}

static char	*free_split(char ***split, char **s)
{
	int		i;

	i = 0;
	while (*split[i])
		free(*split[i++]);
	free(*split);
	free(*s);
	return (NULL);
}

static char	**work(char **split, char *s, char set, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		if (*s != set)
		{
			split[i] = word(s, set);
			if (!split[i])
				return ((char **)(free_split(&split, &s)));
			s = s + ft_strlen(split[i]);
			i++;
		}
		s++;
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(char *s, char set)
{
	char	**split;
	size_t	i;

	i = sentences_size(s, set);
	split = malloc(sizeof(char *) * (i + 1));
	if (!split)
		return (NULL);
	split[i] = NULL;
	return (work(split, s, set, i));
}
