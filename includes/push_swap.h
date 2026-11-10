/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 12:30:57 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/10 16:38:34 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

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
	OP_COUNT
}	t_op;

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	int		size;
}	t_stack;

typedef struct s_ps
{
	t_stack		a;
	t_stack		b;
	int			ops[OP_COUNT];
	const char	*strategy;
	int			bench;
}	t_ps;

void	ft_bzero(void *s, size_t n);
int		ft_atoi_safe(const char *str, int *out);
t_node	*new_node(int value);
void	stack_add_back(t_stack *stack, t_node *node);
int		has_duplicate(t_stack *stack, int value);
void	free_stack(t_stack *stack);
int		build_stack(t_stack *a, int argc, char **argv, int start);
int		ft_strcmp(const char *s1, const char *s2);
int		parse_flags(int argc, char **argv, t_ps *p);

#endif
