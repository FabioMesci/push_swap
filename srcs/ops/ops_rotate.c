/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:17:23 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/11 18:00:26 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_stack *s)
{
	t_node	*node;
	t_node	*last;

	if (s->size < 2)
		return ;
	last = stack_last(s);
	node = s->top;
	s->top = s->top->next;
	last->next = node;
	last->next->next = NULL;
}

void	ra(t_ps *p)
{
	rotate(&p->a);
	log_op(p, OP_RA);
}

void	rb(t_ps *p)
{
	rotate(&p->b);
	log_op(p, OP_RB);
}

void	rr(t_ps *p)
{
	rotate(&p->a);
	rotate(&p->b);
	log_op(p, OP_RR);
}
