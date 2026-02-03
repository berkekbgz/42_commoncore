/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 22:04:08 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/02/02 22:05:07 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FLAG_H
# define FT_PRINTF_FLAG_H

typedef struct s_printf_arg
{
	int		hash;
	int		zero;
	int		minus;
	int		plus;
	int		space;
	int		width;
	int		precision;
}	t_printf_flag;

t_printf_flag	consume_flag(const char	**peek);

#endif
