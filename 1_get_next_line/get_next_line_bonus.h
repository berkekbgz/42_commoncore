/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 21:30:49 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/06/01 18:23:48 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef MAX_OPEN_FD
#  define MAX_OPEN_FD 1024
# endif

# ifndef SEPERATOR
#  define SEPERATOR '\n'
# endif

char	*get_next_line(int fd);
int		has_newline(char *s);
char	*gnl_strndup(char *s, size_t n);
char	*gnl_strdup(char *s);
char	*strjoin_free(char *s1, char *s2, size_t len2);

#endif
