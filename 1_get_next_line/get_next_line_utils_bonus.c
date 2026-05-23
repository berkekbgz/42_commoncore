/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 22:01:24 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/05/23 18:34:19 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	has_newline(char *s)
{
	if (!s)
		return (0);
	while (*s)
		if (*s++ == SEPERATOR)
			return (1);
	return (0);
}

char	*gnl_strndup(char *s, size_t n)
{
	char	*res;
	size_t	i;

	res = malloc(n + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*gnl_strdup(char *s)
{
	return (gnl_strndup(s, gnl_strlen(s)));
}

char	*strjoin_free(char *s1, char *s2, size_t len2)
{
	char	*res;
	size_t	len1;
	size_t	i;

	len1 = gnl_strlen(s1);
	res = malloc(len1 + len2 + 1);
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		res[i] = s2[i - len1];
		i++;
	}
	res[i] = '\0';
	free(s1);
	return (res);
}
