/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:11:21 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/05/01 16:43:10 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_index(t_stack *stack)
{
	t_node	*curr;
	int		max_rank;
	int		max_idx;
	int		i;

	curr = stack->top;
	max_rank = curr->rank;
	max_idx = 0;
	i = 0;
	while (curr)
	{
		if (curr->rank > max_rank)
		{
			max_rank = curr->rank;
			max_idx = i;
		}
		curr = curr->next;
		i++;
	}
	return (max_idx);
}

static void	move_max_to_top(t_state *state)
{
	int	max_idx;
	int	size;

	max_idx = get_max_index(state->b);
	size = state->b->size;
	if (max_idx <= size / 2)
		while (max_idx-- > 0)
			op_rb(state);
	else
	{
		max_idx = size - max_idx;
		while (max_idx-- > 0)
			op_rrb(state);
	}
}

static void	push_chunks_to_b(t_state *state, int chunk_size)
{
	int	pushed;

	pushed = 0;
	while (state->a->size > 0)
	{
		if (state->a->top->rank <= pushed)
		{
			op_pb(state);
			op_rb(state);
			pushed++;
		}
		else if (state->a->top->rank <= pushed + chunk_size)
		{
			op_pb(state);
			pushed++;
		}
		else
			op_ra(state);
	}
}

void	sort_medium(t_state *state)
{
	int	chunk_size;

	if (state->a->size < 2)
		return ;
	chunk_size = sqrt_floor(state->a->size);
	if (chunk_size < 2)
		chunk_size = 2;
	push_chunks_to_b(state, chunk_size);
	while (state->b->size > 0)
	{
		move_max_to_top(state);
		op_pa(state);
	}
}
