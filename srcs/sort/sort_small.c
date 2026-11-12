/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:09:57 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/12 12:53:27 by fmesci           ###   ########.fr       */
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
}
