/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_reverse_rotate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 11:21:20 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/03/08 11:21:46 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "ft_printf.h"
#include <stdlib.h>

static void	rrotate(t_stack *stack)
{
	t_node	*node;

	if (stack->size < 2)
		return ;
	node = stack->bottom;
	stack->bottom = node->prev;
	stack->bottom->next = NULL;
	node->next = stack->top;
	node->prev = NULL;
	stack->top->prev = node;
	stack->top = node;
}

void	op_rra(t_state *state)
{
	rrotate(state->a);
	state->op_count++;
	state->op_counts[OP_RRA]++;
	ft_printf("rra\n");
}

void	op_rrb(t_state *state)
{
	rrotate(state->b);
	state->op_count++;
	state->op_counts[OP_RRB]++;
	ft_printf("rrb\n");
}

void	op_rrr(t_state *state)
{
	rrotate(state->a);
	rrotate(state->b);
	state->op_count++;
	state->op_counts[OP_RRR]++;
	ft_printf("rrr\n");
}
