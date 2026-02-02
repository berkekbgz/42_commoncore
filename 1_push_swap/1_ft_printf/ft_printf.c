/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 19:24:43 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/02/02 17:26:53 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_put/ft_put.h"
#include "libft.h"
#include <stdarg.h>
#include <unistd.h>

int	handle_formatting(const char *peek, va_list *args)
{
	if (*peek == '%')
		return (write(1, "%", 1));
	else if (*peek == 'c')
		return (ft_putchar(va_arg(*args, int)));
	else if (*peek == 's')
		return (ft_putstr(va_arg(*args, char *)));
	else if (*peek == 'p')
		return (ft_putptr(va_arg(*args, void *)));
	else if (*peek == 'd' || *peek == 'i')
		return (ft_putint(va_arg(*args, int)));
	else if (*peek == 'u')
		return (ft_putuint(va_arg(*args, unsigned int)));
	else if (*peek == 'x')
		return (ft_puthex(va_arg(*args, unsigned int), 0));
	else if (*peek == 'X')
		return (ft_puthex(va_arg(*args, unsigned int), 1));
	return (0);
}


int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		ret;
	size_t	count;

	if (!format)
		return (-1);
	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && ft_strchr("cspdiuxX%", format[1]))
		{
			ret = handle_formatting(format + 1, &args);
			format += 2;
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
