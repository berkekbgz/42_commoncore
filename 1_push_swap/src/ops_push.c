/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erearsla <erearsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:02:32 by erearsla          #+#    #+#             */
/*   Updated: 2026/03/08 11:12:24 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "ft_printf.h"
#include <stdlib.h>

static void	push(t_stack *to, t_stack *from)
{
	t_node	*node;

	if (from->size == 0)
		return ;
	node = from->top;
	from->top = node->next;
	if (from->top)
		from->top->prev = NULL;
	else
		from->bottom = NULL;
	from->size--;
	node->next = to->top;
	node->prev = NULL;
	if (to->top)
		to->top->prev = node;
	else
		to->bottom = node;
	to->top = node;
	to->size++;
}

void	op_pa(t_state *state)
{
	push(state->a, state->b);
	state->op_count++;
	state->op_counts[OP_PA]++;
	ft_printf("pa\n");
}

void	op_pb(t_state *state)
{
	push(state->b, state->a);
	state->op_count++;
	state->op_counts[OP_PB]++;
	ft_printf("pb\n");
}
