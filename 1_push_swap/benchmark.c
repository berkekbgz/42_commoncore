/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 16:34:25 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/05/01 16:38:26 by bkabagoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

static void	print_percent(double disorder)
{
	int	percent;
	int	decimal;

	percent = (int)(disorder * 10000.0 + 0.5);
	decimal = percent % 100;
	ft_putnbr_fd(percent / 100, 2);
	ft_putchar_fd('.', 2);
	if (decimal < 10)
		ft_putchar_fd('0', 2);
	ft_putnbr_fd(decimal, 2);
	ft_putstr_fd("%\n", 2);
}

static void	print_complexity(t_strategy strategy)
{
	if (strategy == STRATEGY_SIMPLE)
		ft_putstr_fd("O(n^2)\n", 2);
	else if (strategy == STRATEGY_MEDIUM)
		ft_putstr_fd("O(n sqrt(n))\n", 2);
	else
		ft_putstr_fd("O(n log n)\n", 2);
}

static void	print_strategy(t_state *state)
{
	t_strategy	strategy;

	strategy = state->strategy_flag;
	ft_putstr_fd("[bench] strategy: ", 2);
	if (strategy == STRATEGY_ADAPTIVE)
	{
		ft_putstr_fd("Adaptive / ", 2);
		strategy = state->hidden_strategy;
	}
	else if (strategy == STRATEGY_SIMPLE)
		ft_putstr_fd("Simple / ", 2);
	else if (strategy == STRATEGY_MEDIUM)
		ft_putstr_fd("Medium / ", 2);
	else
		ft_putstr_fd("Complex / ", 2);
	print_complexity(strategy);
}

static void	print_op(char *name, int count)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putnbr_fd(count, 2);
	ft_putchar_fd(' ', 2);
}

void	print_benchmark(t_state *state)
{
	ft_putstr_fd("[bench] disorder: ", 2);
	print_percent(state->disorder);
	print_strategy(state);
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_fd(state->op_count, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("[bench] ", 2);
	print_op("sa", state->op_counts[OP_SA]);
	print_op("sb", state->op_counts[OP_SB]);
	print_op("ss", state->op_counts[OP_SS]);
	print_op("pa", state->op_counts[OP_PA]);
	print_op("pb", state->op_counts[OP_PB]);
	print_op("ra", state->op_counts[OP_RA]);
	print_op("rb", state->op_counts[OP_RB]);
	print_op("rr", state->op_counts[OP_RR]);
	print_op("rra", state->op_counts[OP_RRA]);
	print_op("rrb", state->op_counts[OP_RRB]);
	print_op("rrr", state->op_counts[OP_RRR]);
	ft_putchar_fd('\n', 2);
}
