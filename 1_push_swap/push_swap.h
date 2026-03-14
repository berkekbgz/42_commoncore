/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erearsla <erearsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:59:44 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/03/14 16:56:35 by erearsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef enum e_op
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	N_OP_COUNT
}	t_op;

typedef struct s_node
{
	int				value;
	int				rank;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct s_stack
{
	t_node	*top;
	t_node	*bottom;
	int		size;
}			t_stack;

typedef struct s_state
{
	t_stack	*a;
	t_stack	*b;
	double	disorder;
	int		op_count;
	int		op_counts[N_OP_COUNT];
	int		bench_mode;
	int		strategy_flag;
}			t_state;

// Initialization

void	assign_ranks(t_stack *stack);
double	compute_disorder(t_stack *stack);
int		parse_numbers(t_state *state, int argc, char **argv, int arg_start);

// Sort functions

void	sort_simple(t_state *state);
void	sort_medium(t_state *state);
void	sort_complex(t_state *state);
void	sort_adaptive(t_state *state);

// Swap functions

void	op_sa(t_state *state);
void	op_sb(t_state *state);
void	op_ss(t_state *state);

// Push functions

void	op_pa(t_state *state);
void	op_pb(t_state *state);

// Rotate functions

void	op_ra(t_state *state);
void	op_rb(t_state *state);
void	op_rr(t_state *state);

// Reverse rotate functions

void	op_rra(t_state *state);
void	op_rrb(t_state *state);
void	op_rrr(t_state *state);

// Utils

int		sqrt_floor(int value);
void	print_benchmark(t_state *state);
int		is_sorted(t_stack *stack);
long	ft_atol(char *str);
int		ft_isint(long l);
int		ft_iswhitespace(int c);

// Data Utils

t_node	*new_node(int value, int rank);
t_stack	*new_stack(void);
void	stack_push_bottom(t_stack *stack, int value, int rank);
int		stack_push(t_stack *stack, int value);
t_state	*new_state(void);
void	free_state(t_state *state);

#endif
