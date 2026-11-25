/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:09:54 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/12 18:51:02 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	send_from_a(t_ps *p, int dest)
{
	if (dest == BA)
		ra(p);
	else if (dest == TB || dest == BB)
	{
		pb(p);
		if (dest == BB)
			rb(p);
	}
}

static void	send_from_b(t_ps *p, int dest)
{
	if (dest == TA || dest == BA)
	{
		pa(p);
		if (dest == BA)
			ra(p);
	}
	else if (dest == BB)
		rb(p);
}

int	elem_index(t_ps *p, int loc)
{
	if (loc == TA)
		return (p->a.top->index);
	if (loc == BA)
		return (stack_last(&p->a)->index);
	if (loc == TB)
		return (p->b.top->index);
	return (stack_last(&p->b)->index);
}

void	move_elem(t_ps *p, int loc, int dest)
{
	if (loc == BA)
		rra(p);
	else if (loc == BB)
		rrb(p);
	if (loc == TA || loc == BA)
		send_from_a(p, dest);
	else
		send_from_b(p, dest);
}
