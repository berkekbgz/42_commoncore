/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 11:12:07 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/05/09 14:36:05 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_min_index(t_stack *stack)
{
	t_node	*curr;
	int		min_rank;
	int		min_idx;
	int		i;

	curr = stack->top;
	min_rank = curr->rank;
	min_idx = 0;
	i = 0;
	while (curr)
	{
		if (curr->rank < min_rank)
		{
			min_rank = curr->rank;
			min_idx = i;
		}
		curr = curr->next;
		i++;
	}
	return (min_idx);
}

static void	move_min_to_top(t_state *state)
{
	int	min_idx;
	int	size;

	min_idx = get_min_index(state->a);
	size = state->a->size;
	if (min_idx <= size / 2)
		while (min_idx-- > 0)
			op_ra(state);
	else
	{
		min_idx = size - min_idx;
		while (min_idx-- > 0)
			op_rra(state);
	}
}

static void	sort_three(t_state *state)
{
	int	a;
	int	b;
	int	c;

	a = state->a->top->rank;
	b = state->a->top->next->rank;
	c = state->a->bottom->rank;
	if (a > b && b < c && a < c)
		op_sa(state);
	else if (a > b && b > c)
	{
		op_sa(state);
		op_rra(state);
	}
	else if (a > b && b < c && a > c)
		op_ra(state);
	else if (a < b && b > c && a < c)
	{
		op_sa(state);
		op_ra(state);
	}
	else if (a < b && b > c && a > c)
		op_rra(state);
}

void	sort_small(t_state *state)
{
	while (state->a->size > 3)
	{
		move_min_to_top(state);
		op_pb(state);
	}
	if (state->a->size == 2)
	{
		if (state->a->top->rank > state->a->top->next->rank)
			op_sa(state);
	}
	else if (state->a->size == 3)
		sort_three(state);
	while (state->b->size > 0)
		op_pa(state);
}
