/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 00:18:42 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/02/02 17:51:10 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_put.h"
#include <unistd.h>

static int	puthex_recursive(unsigned long long val, char *hex)
{
	int	count;
	int	ret;

	count = 0;
	if (val >= 16)
		count = puthex_recursive(val / 16, hex);
	if (count == -1)
		return (-1);
	ret = write(1, &hex[val % 16], 1);
	if (ret == -1)
		return (-1);
	return (count + ret);
}

int	ft_puthex(unsigned long long val, char use_upper, char use_alternate)
{
	char	*hex;
	char	ret;

	if (use_alternate)
		ret = write(1, "0x", 2);
	if (ret == -1)
		return (-1);
	if (use_upper)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	if (val == 0)
		return (write(1, "0", 1));
	return (ret + puthex_recursive(val, hex));
}
