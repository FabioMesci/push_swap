/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:09:54 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/12 18:51:02 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	dest_of(int loc, int cls)
{
	if (cls == 0)
	{
		if (loc == TA)
			return (BA);
		return (TA);
	}
	if (cls == 1)
	{
		if (loc == TA || loc == BA)
			return (TB);
		return (BA);
	}
	if (loc == BB)
		return (TB);
	return (BB);
}

static int	to_top(t_ps *p, int loc, int n)
{
	if (loc == BA && p->a.size == n)
		return (TA);
	if (loc == BB && p->b.size == n)
		return (TB);
	return (loc);
}

static void	partition(t_ps *p, int loc, int lo, int n)
{
	int	third;
	int	two;
	int	i;
	int	v;

	third = lo + n / 3;
	two = lo + 2 * n / 3;
	i = 0;
	while (i++ < n)
	{
		v = elem_index(p, loc);
		move_elem(p, loc, dest_of(loc, (v < two) + (v < third)));
	}
}

static void	sort_block(t_ps *p, int loc, int lo, int n)
{
	if (n <= 0)
		return ;
	loc = to_top(p, loc, n);
	if (n == 1)
		return (move_elem(p, loc, TA));
	if (loc == TA && is_ordered(&p->a, n, 1))
		return ;
	if (loc == TB && is_ordered(&p->b, n, 0))
		return (flush_b(p, n));
	if (n == 2 && loc == TA)
		return (sa(p));
	if (n == 2 && loc == TB)
	{
		sb(p);
		return (flush_b(p, 2));
	}
	partition(p, loc, lo, n);
	sort_block(p, dest_of(loc, 0), lo + 2 * n / 3, n - 2 * n / 3);
	sort_block(p, dest_of(loc, 1), lo + n / 3, 2 * n / 3 - n / 3);
	sort_block(p, dest_of(loc, 2), lo, n / 3);
}

void	sort_complex(t_ps *p)
{
	if (check_if_sorted(&p->a))
		return ;
	sort_block(p, TA, 0, p->a.size);
}
