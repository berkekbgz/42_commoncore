/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:01:31 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/03/08 13:10:37 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

t_node	*new_node(int value, int rank)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->rank = rank;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_stack	*new_stack(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
	return (stack);
}

void	stack_push_bottom(t_stack *stack, int value, int rank)
{
	t_node	*node;

	node = new_node(value, rank);
	if (!node)
		return ;
	if (!stack->top)
	{
		stack->top = node;
		stack->bottom = node;
	}
	else
	{
		node->prev = stack->bottom;
		stack->bottom->next = node;
		stack->bottom = node;
	}
	stack->size++;
}

t_state	*new_state(void)
{
	t_state	*state;
	int		i;

	state = malloc(sizeof(t_state));
	if (!state)
		return (NULL);
	state->a = new_stack();
	state->b = new_stack();
	state->op_count = 0;
	state->disorder = 0.0;
	i = 0;
	while (i < N_OP_COUNT)
		state->op_counts[i++] = 0;
	return (state);
}
