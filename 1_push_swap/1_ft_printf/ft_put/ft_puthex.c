/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 00:18:42 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/02/02 00:24:26 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_puthex(unsigned long long val, int use_upper)
{
	char	*hex;

	if (use_upper)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	if (val == 0)
		return (write(1, "0", 1));
	return (puthex_recursive(val, hex));
}