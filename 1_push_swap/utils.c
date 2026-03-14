/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erearsla <erearsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 12:36:04 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/03/14 16:51:52 by erearsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	sqrt_floor(int value)
{
	int	i;

	i = 1;
	while (i * i <= value)
		i++;
	return (i - 1);
}

int		ft_iswhitespace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int		ft_isint(long l)
{
	return (l <= INT_MAX && l >= INT_MIN);
}

long	ft_atol(char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
