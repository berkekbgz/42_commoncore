/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 17:37:21 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/05/01 17:46:48 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"
#include <limits.h>

static int	check_arg(char *s)
{
	int	digit_len;

	digit_len = 0;
	while (ft_iswhitespace(*s))
		s++;
	if (*s == '-' || *s == '+')
		s++;
	if (!*s || !ft_isdigit(*s))
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		digit_len++;
		if (digit_len > 11)
			return (0);
		s++;
	}
	return (1);
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

static int	value_exists(t_stack *stack, long value)
{
	t_node	*node;

	node = stack->top;
	while (node)
	{
		if (node->value == value)
			return (1);
		node = node->next;
	}
	return (0);
}

static int	parse_parts(t_state *state, char **parts)
{
	int		i;
	long	value;

	if (!parts[0])
		return (0);
	i = 0;
	while (parts[i])
	{
		if (!check_arg(parts[i]))
			return (0);
		value = ft_atol(parts[i]);
		if (value > INT_MAX || value < INT_MIN || value_exists(state->a, value))
			return (0);
		if (!stack_push_bottom(state->a, (int)value, 0))
			return (0);
		i++;
	}
	return (1);
}

int	parse_numbers(t_state *state, int argc, char **argv)
{
	int		arg;
	char	**parts;

	arg = 1;
	while (arg < argc)
	{
		if (ft_strncmp(argv[arg], "--", 2) == 0)
		{
			arg++;
			continue ;
		}
		parts = ft_split(argv[arg], ' ');
		if (!parts)
			return (0);
		if (!parse_parts(state, parts))
		{
			free_split(parts);
			return (0);
		}
		free_split(parts);
		arg++;
	}
	return (1);
}
