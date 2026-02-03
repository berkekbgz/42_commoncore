/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:47:39 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/02/02 22:06:13 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"
#include <unistd.h>

int	ft_putuint(unsigned int u)
{
	int		count;
	char	c;
	int		ret;

	count = 0;
	if (u >= 10)
		count = ft_putuint(u / 10);
	if (count == -1)
		return (-1);
	c = (u % 10) + '0';
	ret = write(1, &c, 1);
	if (ret == -1)
		return (-1);
	return (count + ret);
}

int	ft_putint(int i)
{
	int		count;
	int		ret;

	if (i == -2147483648)
		return (write(1, "-2147483648", 11));
	count = 0;
	if (i < 0)
	{
		count = write(1, "-", 1);
		ret = ft_putuint(-i);
		if (ret == -1)
			return (-1);
		return (count + ret);
	}
	ret = ft_putuint(i);
	if (ret == -1)
		return (-1);
	return (ret);
}
