/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 23:47:10 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/02/02 00:30:22 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"
#include <unistd.h>

int	ft_putptr(void *p)
{
	unsigned long long	val;
	int					count;
	int					ret;

	if (!p)
		return (write(1, "(nil)", 5));
	val = (unsigned long long)p;
	count = write(1, "0x", 2);
	if (count == -1)
		return (-1);
	ret = ft_puthex(val, 0);
	if (ret == -1)
		return (-1);
	return (count + ret);
}
