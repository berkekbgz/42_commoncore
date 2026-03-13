/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:58:34 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/03/13 21:14:31 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
