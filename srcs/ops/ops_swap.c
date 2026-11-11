/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:14:55 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/11 18:50:18 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack *s)
{
	t_node	*first;
	t_node	*second;
	t_node	*rest;

	if (s->size < 2)
		return ;
	first = s->top;
	second = first->next;
	rest = second->next;
	s->top = second;
	first->next = rest;
	second->next = first;
}

void	sa(t_ps *p)
{
	swap(&p->a);
	log_op(p, OP_SA);
}

void	sb(t_ps *p)
{
	swap(&p->b);
	log_op(p, OP_SB);
}

void	ss(t_ps *p)
{
	swap(&p->a);
	swap(&p->b);
	log_op(p, OP_SS);
}
