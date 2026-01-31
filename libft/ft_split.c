/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 14:41:28 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/01/31 15:37:37 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*next_word(char const *s, char c, size_t *appendix_out)
{
	size_t	word_len;
	char	*word;

	while (s[*appendix_out] && s[*appendix_out] == c)
		(*appendix_out)++;
	word_len = 0;
	while (s[*appendix_out + word_len] && s[*appendix_out + word_len] != c)
		word_len++;
	word = ft_substr(s, *appendix_out, word_len);
	*appendix_out += word_len;
	return (word);
}

char	**free_on_err(char **arr, size_t i)
{
	while (i > 0)
		free(arr[--i]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	word_count;
	size_t	i;
	size_t	appendix;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!arr)
		return (NULL);
	appendix = 0;
	i = 0;
	while (i < word_count)
	{
		arr[i] = next_word(s, c, &appendix);
		if (!arr[i])
			return (free_on_err(arr, i));
		i++;
	}
	arr[word_count] = NULL;
	return (arr);
}
