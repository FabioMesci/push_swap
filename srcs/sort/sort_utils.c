/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:09:54 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/25 13:11:49 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
