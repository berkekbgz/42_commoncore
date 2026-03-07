/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 22:01:26 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/03/07 22:01:27 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	allocate_remainder(char ***remainder)
{
	long	max_fd;
	long	i;

	max_fd = sysconf(_SC_OPEN_MAX);
	if (!*remainder)
	{
		*remainder = malloc(sizeof(char *) * max_fd);
		if (!*remainder)
			return (0);
		i = 0;
		while (i < max_fd)
			(*remainder)[i++] = NULL;
	}
	return (1);
}

static char	*extract_line(char **remainder)
{
	char	*line;
	char	*left;
	size_t	i;

	i = 0;
	while ((*remainder)[i] && (*remainder)[i] != '\n')
		i++;
	if ((*remainder)[i] == '\n')
		i++;
	line = gnl_strndup(*remainder, i);
	if (!line)
		return (NULL);
	left = gnl_strdup(*remainder + i);
	free(*remainder);
	if (!left || !left[0])
	{
		free(left);
		*remainder = NULL;
	}
	else
		*remainder = left;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	**remainder;
	char		buf[BUFFER_SIZE + 1];
	ssize_t		ret;

	if (fd < 0 || fd >= sysconf(_SC_OPEN_MAX))
		return (NULL);
	if (!allocate_remainder(&remainder))
		return (NULL);
	while (1)
	{
		if (remainder[fd] && has_newline(remainder[fd]))
			return (extract_line(&remainder[fd]));
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret <= 0)
		{
			if (ret == 0 && remainder[fd] && remainder[fd][0])
				return (extract_line(&remainder[fd]));
			return (NULL);
		}
		buf[ret] = '\0';
		remainder[fd] = strjoin_free(remainder[fd], buf, ret);
		if (!remainder[fd])
			return (NULL);
	}
}
