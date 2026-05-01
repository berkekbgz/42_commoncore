/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:56:56 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/05/01 16:43:21 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_bits(int value)
{
	int	bits;

	bits = 0;
	while ((value >> bits) != 0)
		bits++;
	return (bits);
}

void	sort_complex(t_state *state)
{
	int	bit;
	int	i;
	int	size;
	int	max_bits;

	size = state->a->size;
	if (size < 2)
		return ;
	max_bits = get_max_bits(size - 1);
	bit = 0;
	while (bit < max_bits)
	{
		i = 0;
		while (i++ < size)
		{
			if (((state->a->top->rank >> bit) & 1) == 1)
				op_ra(state);
			else
				op_pb(state);
		}
		while (state->b->size > 0)
			op_pa(state);
		bit++;
	}
}
