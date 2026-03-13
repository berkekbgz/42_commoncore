/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 11:16:39 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/03/08 11:20:05 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "ft_printf.h"
#include <stdlib.h>

static void	rotate(t_stack *stack)
{
	t_node	*node;

	if (stack->size < 2)
		return ;
	node = stack->top;
	stack->top = node->next;
	stack->top->prev = NULL;
	node->prev = stack->bottom;
	node->next = NULL;
	stack->bottom->next = node;
	stack->bottom = node;
}

void	op_ra(t_state *state)
{
	rotate(state->a);
	state->op_count++;
	state->op_counts[OP_RA]++;
	ft_printf("ra\n");
}

void	op_rb(t_state *state)
{
	rotate(state->b);
	state->op_count++;
	state->op_counts[OP_RB]++;
	ft_printf("rb\n");
}

void	op_rr(t_state *state)
{
	rotate(state->a);
	rotate(state->b);
	state->op_count++;
	state->op_counts[OP_RR]++;
	ft_printf("rr\n");
}
