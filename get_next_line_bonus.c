/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:50:27 by kaboussi          #+#    #+#             */
/*   Updated: 2022/11/17 11:42:52 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*s[10240];
	char		*buf;
	char		*l;
	ssize_t		bibo;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (ft_strchr(s[fd], '\n') == NULL)
	{
		bibo = read(fd, buf, BUFFER_SIZE);
		if (bibo <= 0)
		{
			if (!s[fd])
				return (free(buf), NULL);
			if (!*s[fd])
				return (free(buf), free(s[fd]), s[fd] = NULL, NULL);
			return (free(buf), l = stdup(s[fd]), free(s[fd]), s[fd] = NULL, l);
		}
		buf[bibo] = '\0';
		s[fd] = ft_strjoin(s[fd], buf);
	}
	return (l = get_line(s[fd]), s[fd] = rest_line(s[fd]), free(buf), l);
}
