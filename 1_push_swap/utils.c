/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erearsla <erearsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 12:36:04 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/03/14 17:51:16 by erearsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"
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

int		is_sorted(t_stack *stack)
{
	t_node *node;

	if (!stack || !stack->top)
		return (1);
	node = stack->top;
	while (node->next)
	{
		if (node->value > node->next->value)
			return (0);
		node = node->next;
	}
	return (1);
}


static void put_bench()
{
	ft_putstr_fd("[BENCH] ", 2);
}

void	print_benchmark(t_state *state)
{
	put_bench();
	ft_putstr_fd("disorder: ", 2);
	ft_putstr_fd(ft_itoa(), 2);
	
}