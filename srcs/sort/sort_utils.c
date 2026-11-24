/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:09:54 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/12 18:51:02 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	max_bits(t_stack *s)
{
	t_node	*cur;
	int		max;
	int		bits;

	cur = s->top;
	max = 0;
	while (cur)
	{
		if (cur->index > max)
			max = cur->index;
		cur = cur->next;
	}
	bits = 0;
	while (max >> bits)
		bits++;
	return (bits);
}

int	is_ordered(t_stack *s, int len, int asc)
{
	t_node	*cur;

	cur = s->top;
	while (--len > 0)
	{
		if (asc && cur->index > cur->next->index)
			return (0);
		if (!asc && cur->index < cur->next->index)
			return (0);
		cur = cur->next;
	}
	return (1);
}

void	flush_b(t_ps *p, int len)
{
	while (len-- > 0)
		pa(p);
}
