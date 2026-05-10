/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erearsla <erearsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:28:07 by erearsla          #+#    #+#             */
/*   Updated: 2026/05/10 16:25:16 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static int	set_strategy(char *arg, t_state *state)
{
	if (ft_strncmp(arg, "--bench", 8) == 0)
		state->bench_mode = 1;
	else if (ft_strncmp(arg, "--simple", 9) == 0
		&& state->strategy_flag == STRATEGY_UNKNOWN)
		state->strategy_flag = STRATEGY_SIMPLE;
	else if (ft_strncmp(arg, "--medium", 9) == 0
		&& state->strategy_flag == STRATEGY_UNKNOWN)
		state->strategy_flag = STRATEGY_MEDIUM;
	else if (ft_strncmp(arg, "--complex", 10) == 0
		&& state->strategy_flag == STRATEGY_UNKNOWN)
		state->strategy_flag = STRATEGY_COMPLEX;
	else if (ft_strncmp(arg, "--adaptive", 11) == 0
		&& state->strategy_flag == STRATEGY_UNKNOWN)
		state->strategy_flag = STRATEGY_ADAPTIVE;
	else
		return (0);
	return (1);
}

static int	parse_flags(int argc, char **argv, t_state *state)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strncmp(argv[i], "--", 2) == 0)
		{
			if (!set_strategy(argv[i], state))
				return (0);
		}
		i++;
	}
	return (1);
}

static void	set_hidden_strategy(t_state *state)
{
	if (state->strategy_flag == STRATEGY_SIMPLE)
		state->hidden_strategy = STRATEGY_SIMPLE;
	else if (state->strategy_flag == STRATEGY_MEDIUM)
		state->hidden_strategy = STRATEGY_MEDIUM;
	else if (state->strategy_flag == STRATEGY_COMPLEX)
		state->hidden_strategy = STRATEGY_COMPLEX;
	else if (state->disorder < 0.2)
		state->hidden_strategy = STRATEGY_SIMPLE;
	else if (state->disorder < 0.5)
		state->hidden_strategy = STRATEGY_MEDIUM;
	else
		state->hidden_strategy = STRATEGY_COMPLEX;
}

static void	execute_sort(t_state *state)
{
	assign_ranks(state->a);
	state->disorder = compute_disorder(state->a);
	set_hidden_strategy(state);
	if (is_sorted(state->a))
		return ;
	if (state->a->size <= 5)
		return (sort_small(state));
	if (state->strategy_flag == STRATEGY_SIMPLE)
		sort_simple(state);
	else if (state->strategy_flag == STRATEGY_MEDIUM)
		sort_medium(state);
	else if (state->strategy_flag == STRATEGY_COMPLEX)
		sort_complex(state);
	else if (state->strategy_flag == STRATEGY_ADAPTIVE)
		sort_adaptive(state);
}

int	main(int argc, char **argv)
{
	t_state	*state;

	if (argc < 2)
		return (0);
	state = new_state();
	if (!state || !parse_flags(argc, argv, state)
		|| !parse_numbers(state, argc, argv))
	{
		write(2, "Error\n", 6);
		free_state(state);
		return (1);
	}
	if (state->strategy_flag == STRATEGY_UNKNOWN)
		state->strategy_flag = STRATEGY_ADAPTIVE;
	if (state->a->size == 0)
	{
		free_state(state);
		return (0);
	}
	if (state->a->size > 0)
		execute_sort(state);
	if (state->bench_mode)
		print_benchmark(state);
	free_state(state);
	return (0);
}
