/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelfkih <ebelfkih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 06:36:28 by ebelfkih          #+#    #+#             */
/*   Updated: 2023/03/15 10:15:08 by ebelfkih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	if (!s)
		return (-1);
	i = 0;
	str = (char *)s;
	while (str[i] && str[i] != (char)c)
		i++;
	if (str[i] == (char)c)
		return (i);
	return (-1);
}

char	*join(char **buffer, char **s)
{
	char	*t;

	t = *s;
	*s = ft_strjoin(*buffer, t);
	free (t);
	t = NULL;
	free (*buffer);
	*buffer = NULL;
	if (**s == '\0')
	{
		free (*s);
		return (NULL);
	}
	return (*s);
}

char	*return_line(char **buffer, char **s1)
{
	char	*s;
	char	*s2;
	int		i;

	if (!*s1 && !*buffer)
		return (NULL);
	if (!buffer)
		return (ft_strdup(*s1));
	i = ft_strchr(*buffer, '\n');
	s2 = ft_substr(*buffer, 0, i + 1);
	s = join(s1, &s2);
	*s1 = ft_substr(*buffer, i + 1, BUFFER_SIZE);
	free (*buffer);
	*buffer = NULL;
	return (s);
}

void	buffer_plen(char **buffer, char **s1, int *r, int fd)
{
	if (ft_strchr(*s1, '\n') < 0)
	{
		*buffer = ft_calloc(BUFFER_SIZE + 1, 1);
		*r = read(fd, *buffer, BUFFER_SIZE);
	}
	else
	{
		*buffer = ft_strdup(*s1);
		free (*s1);
		*s1 = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*s1;
	char		*buffer;
	int			r;

	r = 1;
	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (r)
	{
		buffer_plen(&buffer, &s1, &r, fd);
		if (!buffer)
			return (free(s1), NULL);
		if (r < BUFFER_SIZE && ft_strchr(buffer, '\n') < 0)
			return (join (&s1, &buffer));
		else if (ft_strchr(buffer, '\n') >= 0)
			return (return_line(&buffer, &s1));
		else
			s1 = join (&s1, &buffer);
	}
	return (NULL);
}
