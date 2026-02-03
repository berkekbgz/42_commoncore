/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 19:24:43 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/02/02 22:05:48 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_put/ft_put.h"
#include "ft_printf_flag.h"
#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

static int	try_parse_formatting(const char *peek, va_list *args,
	int *consume)
{
	t_printf_flag	flag;
	const char		*start;

	start = peek;
	flag = consume_flag(&peek);
	*consume = (peek - start) + 2;
	if (*peek == '%')
		return (write(1, "%", 1));
	else if (*peek == 'c')
		return (ft_putchar(va_arg(*args, int)));
	else if (*peek == 's')
		return (ft_putstr(va_arg(*args, char *), -1));
	else if (*peek == 'p')
		return (ft_putptr(va_arg(*args, void *)));
	else if (*peek == 'd' || *peek == 'i')
		return (ft_putint(va_arg(*args, int)));
	else if (*peek == 'u')
		return (ft_putuint(va_arg(*args, unsigned int)));
	else if (*peek == 'x')
		return (ft_puthex(va_arg(*args, unsigned int), 0, flag.hash));
	else if (*peek == 'X')
		return (ft_puthex(va_arg(*args, unsigned int), 1, flag.hash));
	*consume = 1;
	return (write(1, "%", 1));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		ret;
	size_t	count;
	int		consume;

	if (!format)
		return (-1);
	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			consume = 0;
			ret = try_parse_formatting(format + 1, &args, &consume);
			format += consume;
		}
		else
			ret = write(1, format++, 1);
		if (ret == -1)
			return (-1);
		count += ret;
	}
	va_end(args);
	return (count);
}
