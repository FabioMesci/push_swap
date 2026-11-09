/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 12:30:57 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/09 16:30:43 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

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
	t_stack	a;
	t_stack	b;
	int		ops[11];
}	t_ps;

void	ft_bzero(void *s, size_t n);
int		ft_atoi_safe(const char *str, int *out);
t_node	*new_node(int value);
void	stack_add_back(t_stack *stack, t_node *node);
int		has_duplicate(t_stack *stack, int value);
void	free_stack(t_stack *stack);
int		build_stack(t_stack *a, int argc, char **argv);

#endif
