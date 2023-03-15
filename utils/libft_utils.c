/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 08:02:00 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/15 11:35:14 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	n_of_world(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (*s == '\0')
		return (0);
	if (s[i] != c)
		j++;
	while (s[++i])
		if (s[i] != c && s[i - 1] == c)
			j++;
	return (j);
}

int	ft_clear(char **spl, int p)
{
	int	i;

	i = 0;
	while (i < p && spl[i])
		free(spl[i++]);
	free(spl);
	return (-1);
}

int	plen(char **spl, const char *s, char c)
{
	int			i;
	size_t		p;
	size_t		len;
	int			start;

	i = -1;
	len = 0;
	p = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i++] != c && s[i - 1])
				len++;
			spl[p++] = ft_substr(s, start, len);
			if (spl[p - 1] == NULL)
				return (ft_clear(spl, p));
			len = 0;
			i -= 2;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**spl;

	if (!s)
		return (NULL);
	spl = malloc((n_of_world(s, c) + 1) * sizeof(char *));
	if (!spl)
		return (NULL);
	spl[n_of_world(s, c)] = NULL;
	if (plen(spl, s, c) < 0)
		return (NULL);
	return (spl);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s)
		return (NULL);
	while (s1[++i])
		s[i] = s1[i];
	while (s2[++j])
		s[i++] = s2[j];
	s[i] = '\0';
	return (s);
}
