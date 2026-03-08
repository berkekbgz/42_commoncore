/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erearsla <erearsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:02:35 by erearsla          #+#    #+#             */
/*   Updated: 2026/03/08 13:19:17 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "ft_printf.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	static t_state	*state;

	(void)argc;
	(void)argv;

	state = new_state();
	// stack_push_bottom(state->a, 20, 3);
	// stack_push_bottom(state->a, 10, 1);
	// stack_push_bottom(state->a, 21, 4);
	// stack_push_bottom(state->a, 3,  0);
	// stack_push_bottom(state->a, 14, 2);
	stack_push_bottom(state->a, 5, 4);
	stack_push_bottom(state->a, 4, 3);
	stack_push_bottom(state->a, 3, 2);
	stack_push_bottom(state->a, 2,  1);
	stack_push_bottom(state->a, 1, 0);

	sort_medium(state);


	// t_node *node = state->a->top;
	// while (1)
	// {
	// 	ft_printf("%d ", node->value);
	// 	if (!node->next)
	// 	{
	// 		ft_printf("\n");
	// 		break ;
	// 	}
	// 	node = node->next;
	// }

	sort_simple(state);

	return (0);
}
