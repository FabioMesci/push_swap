/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 12:30:57 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/11 12:38:16 by fmesci           ###   ########.fr       */
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

/*
** strategy: despues de main nunca es NULL. Valores posibles (exactos):
**   "--simple"   O(n^2)
**   "--medium"   O(n sqrt n)
**   "--complex"  O(n log n)
**   "--adaptive" segun el indice de desorden (por defecto)
*/
typedef struct s_ps
{
	t_stack		a;
	t_stack		b;
	int			ops[OP_COUNT];
	const char	*strategy;
	int			bench;
	double		disorder;
}	t_ps;

/* utils.c */
void		ft_bzero(void *s, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *str);

/* parsing.c */
int			ft_atoi_safe(const char *str, int *out);
int			build_stack(t_stack *a, int argc, char **argv, int start);

/* stack.c */
t_node		*new_node(int value);
void		stack_add_back(t_stack *stack, t_node *node);
int			has_duplicate(t_stack *stack, int value);
void		free_stack(t_stack *stack);

/* flags.c */
int			parse_flags(int argc, char **argv, t_ps *p);

/* ops_utils.c */
const char	*op_name(t_op op);
void		log_op(t_ps *p, t_op op);

/* ops_push.c */
void		pa(t_ps *p);
void		pb(t_ps *p);

#endif
