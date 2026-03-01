/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:51:58 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/02/27 16:51:58 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_flag.h"
#include "libft.h"

static int	parse_number(const char **peek)
{
	int	n;

	n = ft_atoi(*peek);
	while (ft_isdigit(**peek))
		(*peek)++;
	return (n);
}

t_printf_flag	consume_flag(const char	**peek)
{
	t_printf_flag	arg;

	arg = (t_printf_flag){0};
	while (**peek && ft_strchr("-0# +", **peek))
	{
		if (**peek == '-')
			arg.minus = 1;
		else if (**peek == '0')
			arg.zero = 1;
		else if (**peek == '#')
			arg.hash = 1;
		else if (**peek == ' ')
			arg.space = 1;
		else if (**peek == '+')
			arg.plus = 1;
		(*peek)++;
	}
	if (ft_isdigit(**peek))
		arg.width = parse_number(peek);
	if (**peek == '.')
	{
		(*peek)++;
		arg.precision = parse_number(peek);
	}
	return (arg);
}
