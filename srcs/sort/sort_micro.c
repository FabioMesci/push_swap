/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_micro.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:09:54 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/12 18:51:02 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static const char	*tab_a(void)
{
	return (".........eeadd....ead......eeadad...eaeadd...eaeadad.."
		"a........eecdd....eada.....eeadada..eaecdd...eaeadada."
		"aead.....eecdad...aeada....eecdada..eaecdad..eaecdada."
		"aeaeadd..aeaeadad.aeaecdd..eecfdadi.aeaecdad.aeaecdada");
}

static const char	*tab_b(void)
{
	return ("bdhbddkd.bdhddkd..ddcfdadi.bdbdcdd..ddcdada..dfdddi..."
		"dhbddkd..dhddkd...bddhdakd.bdbdadd..ddcdad...bdbddd..."
		"dbdhdakd.dbdcdd...ddhdakd..dbdadd...ddcdd....bdddd...."
		"dbdbdad..dbdbdd...ddbdad...dbddd....ddbdd....dddd.....");
}

static void	apply_op(t_ps *p, char c)
{
	if (c == 'a')
		sa(p);
	if (c == 'b')
		sb(p);
	if (c == 'c')
		ss(p);
	if (c == 'd')
		pa(p);
	if (c == 'e')
		pb(p);
	if (c == 'f')
		ra(p);
	if (c == 'g')
		rb(p);
	if (c == 'h')
		rr(p);
	if (c == 'i')
		rra(p);
	if (c == 'j')
		rrb(p);
	if (c == 'k')
		rrr(p);
}

static int	lehmer(t_node *cur)
{
	int	v[4];
	int	i;
	int	j;
	int	idx;
	int	c;

	i = -1;
	while (++i < 4)
	{
		v[i] = cur->index;
		cur = cur->next;
	}
	idx = 0;
	i = -1;
	while (++i < 3)
	{
		c = 0;
		j = i;
		while (++j < 4)
			c += (v[j] < v[i]);
		idx = idx * (4 - i) + c;
	}
	return (idx);
}

/*
** Sorts the 4 top numbers of a (from_b = 0) or moves the 4 top numbers of
** b onto a, sorted (from_b = 1), with the fewest possible operations.
** The sequences come from an exhaustive search (see README).
*/
void	micro_four(t_ps *p, int from_b)
{
	const char	*seq;
	int			i;

	if (from_b)
		seq = tab_b() + lehmer(p->b.top) * 9;
	else
		seq = tab_a() + lehmer(p->a.top) * 9;
	i = 0;
	while (i < 9 && seq[i] != '.')
		apply_op(p, seq[i++]);
}
