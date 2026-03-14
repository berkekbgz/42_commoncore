/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erearsla <erearsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:28:07 by erearsla          #+#    #+#             */
/*   Updated: 2026/03/14 16:08:08 by erearsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static void	set_strategy(char *arg, t_state *state)
{
	if (ft_strncmp(arg, "--bench", 8) == 0)
		state->bench_mode = 1;
	else if (ft_strncmp(arg, "--simple", 9) == 0)
		state->strategy_flag = 1;
	else if (ft_strncmp(arg, "--medium", 9) == 0)
		state->strategy_flag = 2;
	else if (ft_strncmp(arg, "--complex", 10) == 0)
		state->strategy_flag = 3;
	else if (ft_strncmp(arg, "--adaptive", 11) == 0)
		state->strategy_flag = 0;
}

static int	parse_flags(int argc, char **argv, t_state *state)
{
	int	i;

	i = 1;
	state->strategy_flag = 0;
	state->bench_mode = 0;
	while (i < argc)
	{
		if (ft_strncmp(argv[i], "--", 2) == 0)
			set_strategy(argv[i], state);
		else
			break ;
		i++;
	}
	return (i);
}

static void	execute_sort(t_state *state)
{
	assign_ranks(state->a);
	state->disorder = compute_disorder(state->a);
	if (state->strategy_flag == 1)
		sort_simple(state);
	else if (state->strategy_flag == 2)
		sort_medium(state);
	else if (state->strategy_flag == 3)
		sort_complex(state);
	else
		sort_adaptive(state);
}

int	main(int argc, char **argv)
{
	t_state	*state;
	int		arg_start;

	if (argc < 2)
		return (0);
	state = new_state();
	arg_start = parse_flags(argc, argv, state);
	if (!parse_numbers(state, argc, argv, arg_start))
	{
		write(2, "Error\n", 6);
		free_state(state);
		return (1);
	}
	if (state->a->size > 1 && !is_sorted(state->a))
		execute_sort(state);
	if (state->bench_mode)
		print_benchmark(state);
	free_state(state);
	return (0);
}
