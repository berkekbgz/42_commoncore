/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erearsla <erearsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:03:50 by erearsla          #+#    #+#             */
/*   Updated: 2026/03/08 13:01:45 by erearsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int get_min_index(t_stack *stack)
{
    t_node  *curr;
    int     min_value;
    int     min_idx;
    int     i;

    curr = stack->top;
    min_value = curr->value;
    min_idx = 0;
    i = 0;
    while (curr)
    {
        if (curr->value < min_value)
        {
            min_value = curr->value;
            min_idx = i;
        }
        curr = curr->next;
        i++;
    }
    return (min_idx);
}

void sort_simple(t_state *state)
{
    int min_idx;
    int size;

    while (state->a->size > 0)
    {
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
        op_pb(state);
    }
    while (state->b->size > 0)
        op_pa(state);
}

