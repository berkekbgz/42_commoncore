/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:06:04 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/03/07 20:06:06 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_top(t_stack *stack)
{
	int	tmp;

	if (stack->size < 2)
		return ;
	tmp = stack->top->value;
	stack->top->value = stack->top->next->value;
	stack->top->next->value = tmp;
	tmp = stack->top->rank;
	stack->top->rank = stack->top->rank;
	stack->top->next->rank = tmp;
}

void	op_sa(t_state *state)
{
	swap_top(state->a);
	state->op_count++;
	state->op_counts[OP_SA]++;
	ft_printf("sa\n");
}

void	op_sb(t_state *state)
{
	swap_top(state->b);
	state->op_count++;
	state->op_counts[OP_SB]++;
	ft_printf("sb\n");
}

void	op_ss(t_state *state)
{
	swap_top(state->a);
	swap_top(state->b);
	state->op_count++;
	state->op_counts[OP_SS]++;
	ft_printf("ss\n");
}
