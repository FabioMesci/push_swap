/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:09:57 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/12 18:52:12 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_three(t_ps *p)
{
	int	top;
	int	mid;
	int	bottom;

	top = p->a.top->value;
	mid = p->a.top->next->value;
	bottom = p->a.top->next->next->value;
	if (top > mid && top > bottom)
		ra(p);
	else if (mid > top && mid > bottom)
		rra(p);
	top = p->a.top->value;
	mid = p->a.top->next->value;
	if (top > mid)
		sa(p);
}

void	push_min(t_ps *p)
{
	int	pos;
	int	size;
	int	i;

	i = 0;
	size = p->a.size;
	pos = stack_min_pos(&p->a);
	if (pos <= size - pos)
	{
		while (i < pos)
		{
			ra(p);
			i++;
		}
	}
	else
	{
		while (i < size - pos)
		{
			rra(p);
			i++;
		}
	}
	pb(p);
}

static void	sort_four(t_ps *p)
{
	push_min(p);
	sort_three(p);
	pa(p);
}

static void	sort_five(t_ps *p)
{
	push_min(p);
	sort_four(p);
	pa(p);
}

void	sort_small(t_ps *p)
{
	int	top;
	int	bottom;

	if (p->a.size == 2)
	{
		top = p->a.top->value;
		bottom = p->a.top->next->value;
		if (top > bottom)
			sa(p);
	}
	else if (p->a.size == 3)
		sort_three(p);
	else if (p->a.size == 4)
		sort_four(p);
	else if (p->a.size == 5)
		sort_five(p);
}
