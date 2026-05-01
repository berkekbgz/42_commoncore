/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_adaptive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erearsla <erearsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 12:33:36 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/03/14 18:16:57 by erearsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_adaptive(t_state *state)
{
	if (state->disorder < 0.2)
	{
		state->hidden_strategy = STRATEGY_SIMPLE;
		return (sort_simple(state));
	}
	else if (state->disorder < 0.5)
	{
		state->hidden_strategy = STRATEGY_MEDIUM;
		return (sort_medium(state));
	}
	else
	{
		state->hidden_strategy = STRATEGY_COMPLEX;
		return (sort_complex(state));
	}
}
