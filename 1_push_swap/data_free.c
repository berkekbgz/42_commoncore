/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erearsla <erearsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 17:37:47 by erearsla          #+#    #+#             */
/*   Updated: 2026/03/14 17:42:00 by erearsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static void	free_stack(t_stack *stack)
{
	t_node *tmp;
	t_node *next;

	if (!stack)
		return ;

	tmp = stack->top;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(stack);
}

void	free_state(t_state *state)
{
	if (!state)
		return ;

	if (state->a)
	{
		free_stack(state->a);
		state->a = NULL;
	}
	if (state->b)
	{
		free_stack(state->b);
		state->b = NULL;
	}
	free(state);
}