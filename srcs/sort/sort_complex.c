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

static void	sort_a(t_ps *p, int len, int bit);

static int	part_a(t_ps *p, int len, int bit)
{
	int	zeros;
	int	i;

	zeros = 0;
	i = len;
	while (i-- > 0)
	{
		if ((p->a.top->index >> bit) & 1)
			ra(p);
		else
		{
			pb(p);
			zeros++;
		}
	}
	i = len - zeros;
	if (p->a.size != i)
		while (i-- > 0)
			rra(p);
	return (zeros);
}

static int	part_b(t_ps *p, int len, int bit)
{
	int	ones;
	int	i;

	ones = 0;
	i = len;
	while (i-- > 0)
	{
		if ((p->b.top->index >> bit) & 1)
		{
			pa(p);
			ones++;
		}
		else
			rb(p);
	}
	i = len - ones;
	if (p->b.size != i)
		while (i-- > 0)
			rrb(p);
	return (ones);
}

static void	sort_b(t_ps *p, int len, int bit)
{
	int	ones;

	if (len <= 0)
		return ;
	if (len == 1 || bit < 0 || is_ordered(&p->b, len, 0))
		return (flush_b(p, len));
	if (len == 2)
	{
		flush_b(p, 2);
		return (sa(p));
	}
	if (len == 4)
		return (micro_four(p, 1));
	ones = part_b(p, len, bit);
	sort_a(p, ones, bit - 1);
	sort_b(p, len - ones, bit - 1);
}

static void	sort_a(t_ps *p, int len, int bit)
{
	int	zeros;

	if (len <= 1 || bit < 0 || is_ordered(&p->a, len, 1))
		return ;
	if (len == 2)
		return (sa(p));
	if (len == 4)
		return (micro_four(p, 0));
	zeros = part_a(p, len, bit);
	sort_a(p, len - zeros, bit - 1);
	sort_b(p, zeros, bit - 1);
}

void	sort_complex(t_ps *p)
{
	if (check_if_sorted(&p->a))
		return ;
	sort_a(p, p->a.size, max_bits(&p->a) - 1);
}
