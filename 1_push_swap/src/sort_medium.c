/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:11:21 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/03/08 13:11:40 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_medium(t_state *state)
{
	int	chunk_size;
	// int	pos;

	chunk_size = sqrt_floor(state->a->size);
	if (chunk_size < 2)
		chunk_size = 2;
}
