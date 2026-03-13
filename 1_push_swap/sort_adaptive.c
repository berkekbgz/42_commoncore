/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_adaptive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 12:33:36 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/03/13 20:55:44 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_adaptive(t_state *state)
{
	if (state->disorder < 0.2)
		return (sort_simple(state));
	else if (state->disorder < 0.5)
		return (sort_medium(state));
	else
		return (sort_complex(state));
}
