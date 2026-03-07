/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabagoz <bkabagoz@student.42istanbul.com.tr>   +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 18:59:44 by bkabagoz          #+#    #+#             */
/*   Updated: 2026/03/07 20:29:46 by bkabagoz         ###   ########.fr       */
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
	struct s_nde	*prev;
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
	int		op_count;
	int		op_counts[N_OP_COUNT];
}			t_state;

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


#endif
