/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 21:30:49 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/03/07 22:01:20 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);
int		has_newline(char *s);
char	*gnl_strndup(char *s, size_t n);
char	*gnl_strdup(char *s);
char	*strjoin_free(char *s1, char *s2, size_t len2);
size_t	gnl_strlen(char *s);

#endif
