/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erearsla <erearsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:02:37 by erearsla          #+#    #+#             */
/*   Updated: 2026/05/01 17:46:30 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
