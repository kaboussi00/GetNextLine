/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:39:37 by kaboussi          #+#    #+#             */
/*   Updated: 2022/11/17 11:41:31 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *s)
{
	int		i;
	char	*l;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\n')
		i++;
	l = ft_substr(s, 0, i + 1);
	return (l);
}

char	*rest_line(char *s)
{
	int		i;
	char	*rest;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\n')
		i++;
	rest = ft_substr(s, i + 1, ft_strlen(s) - i);
	free(s);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*buf;
	char		*l;
	ssize_t		bibo;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (ft_strchr(s, '\n') == NULL)
	{
		bibo = read(fd, buf, BUFFER_SIZE);
		if (bibo <= 0)
		{
			if (!s)
				return (free(buf), NULL);
			if (!*s)
				return (free(buf), free(s), s = NULL, NULL);
			return (free(buf), l = stdup(s), free(s), s = NULL, l);
		}
		buf[bibo] = '\0';
		s = ft_strjoin(s, buf);
	}
	return (l = get_line(s), s = rest_line(s), free(buf), l);
}
