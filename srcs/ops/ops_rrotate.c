/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rrotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:16:05 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/11 17:59:49 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rrotate(t_stack *s)
{
	t_node	*cur;
	t_node	*last;

	if (s->size < 2)
		return ;
	last = stack_last(s);
	cur = s->top;
	while (cur->next != last)
		cur = cur->next;
	cur->next = NULL;
	last->next = s->top;
	s->top = last;
}

void	rra(t_ps *p)
{
	rrotate(&p->a);
	log_op(p, OP_RRA);
}

void	rrb(t_ps *p)
{
	rrotate(&p->b);
	log_op(p, OP_RRB);
}

void	rrr(t_ps *p)
{
	rrotate(&p->a);
	rrotate(&p->b);
	log_op(p, OP_RRR);
}
