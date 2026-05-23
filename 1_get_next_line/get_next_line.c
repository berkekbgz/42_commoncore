/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 22:01:26 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/05/23 22:10:07 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_ptr(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static int	set_left(char **left, char *remainder, size_t i)
{
	*left = NULL;
	if (remainder[i])
	{
		*left = gnl_strdup(remainder + i);
		if (!*left)
			return (0);
	}
	return (1);
}

static char	*extract_line(char **remainder)
{
	char	*line;
	char	*left;
	size_t	i;

	i = 0;
	while ((*remainder)[i] && (*remainder)[i] != SEPERATOR)
		i++;
	if ((*remainder)[i] == SEPERATOR)
		i++;
	line = gnl_strndup(*remainder, i);
	if (!line)
		return (free_ptr(remainder));
	if (!set_left(&left, *remainder, i))
	{
		free(line);
		return (free_ptr(remainder));
	}
	free(*remainder);
	*remainder = left;
	return (line);
}

static char	*read_file(int fd, char *buf, char **remainder)
{
	ssize_t	ret;

	while (1)
	{
		if (*remainder && has_newline(*remainder))
		{
			free(buf);
			return (extract_line(remainder));
		}
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret <= 0)
		{
			free(buf);
			if (ret == 0 && *remainder && (*remainder)[0])
				return (extract_line(remainder));
			return (free_ptr(remainder));
		}
		buf[ret] = '\0';
		*remainder = strjoin_free(*remainder, buf, ret);
		if (!*remainder)
			return (free_ptr(&buf));
	}
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	return (read_file(fd, buf, &remainder));
}
