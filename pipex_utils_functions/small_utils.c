
#include "../Includes/pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*s;

	i = ft_strlen(s1) + ft_strlen(s2);
	s = malloc(sizeof(char) * i + 1);
	if (!s)
		return (NULL);
	s[i] = '\0';
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s[i] = s2[j];
		i++;
		j++;
	}
	return (s);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s;

	i = ft_strlen(s1);
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	s[i] = '\0';
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	return (s);
}

bool	ft_strncmp(const char *s1, const char *s2, int len)
{
	int		i;

	i = 0;
	while (i < len && s1[i] == s2[i] && s1[i] && s2[i])
	{
		if (++i == len)
			return (true);
	}
	return (false);
}

int	found_occur(char *s, char set)
{
	int		i;

	i = 0;
	while (*s)
	{
		if (*s == set)
			i++;
		s++;
	}
	return (i);
}
