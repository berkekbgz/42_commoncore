/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erearsla <erearsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:02:37 by erearsla          #+#    #+#             */
/*   Updated: 2026/03/14 17:44:36 by erearsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"
#include <limits.h>

void	assign_ranks(t_stack *stack)
{
	t_node	*node_i;
	t_node	*node_j;

	node_i = stack->top;
	while (node_i)
	{
		node_i->rank = 0;
		node_j = stack->top;
		while (node_j)
		{
			if (node_i->value > node_j->value)
				node_i->rank++;
			node_j = node_j->next;
		}
		node_i = node_i->next;
	}
}

double	compute_disorder(t_stack *stack)
{
	double	mistakes;
	int		total_pairs;
	t_node	*node_i;
	t_node	*node_j;

	node_i = stack->top;
	total_pairs = 0;
	mistakes = 0;
	while (node_i)
	{
		node_j = node_i->next;
		while (node_j)
		{
			total_pairs++;
			if (node_i->rank > node_j->rank)
				mistakes++;
			node_j = node_j->next;
		}
		node_i = node_i->next;
	}
	if (total_pairs <= 0)
		return (0);
	return (mistakes / total_pairs);
}

static int	check_arg(char *s)
{
	int digit_len;
	
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

int	parse_numbers(t_state *state, int argc, char **argv, int arg_start)
{
	int		i;
	long	value;
	long	check;

	while (argv[arg_start])
	{
		if (!check_arg(argv[arg_start]))
			return (0);
		value = ft_atol(argv[arg_start]);
		if (value > INT_MAX || value < INT_MIN)
			return (0);
		i = arg_start + 1;
		while (i < argc)
		{
			check = ft_atol(argv[i]);			
			if (value == check)
				return (0);
			i++;
		}
		stack_push_bottom(state->a, (int)value, NULL);
		
		arg_start++;
	}

	return (1);
}
