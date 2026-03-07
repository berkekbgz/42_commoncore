/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 21:41:10 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/03/07 20:53:17 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

#ifndef OPEN_MAX
# define OPEN_MAX 1024
#endif

int	has_newline(char *s, size_t *size)
{
	*size = 0;
	while (s[*size] && s[*size] != '\n')
		(*size)++;
	return (s[*size] == '\n');
}

char	*get_next_line(int fd)
{
	static char	*remainder[OPEN_MAX];
	char		*buf;
	char		*ret;
	int			i;
	size_t		size;

	i = 0;
	while (1)
	{
		buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
		if (!buf)
			return (NULL);
		read(fd, buf, sizeof(buf));
		if (!has_newline(buf, &size))
		{
			remainder[fd] = buf; // TODO: concat here
			continue ;
		}
		// TODO: return here and adjust remainder
		i++;
	}

	return (NULL);
}
