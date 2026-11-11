/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:15:52 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/11 12:47:55 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_stack *dst, t_stack *src)
{
	t_node	*node;

	if (src->top == NULL)
		return ;
	node = src->top;
	src->top = src->top->next;
	node->next = dst->top;
	dst->top = node;
	src->size = src->size - 1;
	dst->size = dst->size + 1;
}

void	pa(t_ps *p)
{
	push(&p->a, &p->b);
	log_op(p, OP_PA);
}

void	pb(t_ps *p)
{
	push(&p->b, &p->a);
	log_op(p, OP_PB);
}
