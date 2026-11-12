/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:21:41 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/12 17:19:46 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*stack_last(t_stack *s)
{
	t_node	*last;
	t_node	*cur;

	if (s == NULL)
		return (NULL);
	cur = s->top;
	last = cur;
	while (cur != NULL)
	{
		last = cur;
		cur = cur->next;
	}
	return (last);
}

int	stack_min_pos(t_stack *s)
{
	int		pos;
	int		min;
	int		min_pos;
	t_node	*cur;

	cur = s->top;
	min = cur->value;
	pos = 0;
	min_pos = 0;
	while (cur != NULL)
	{
		if (min > cur->value)
		{
			min = cur->value;
			min_pos = pos;
		}
		pos++;
		cur = cur->next;
	}
	return (min_pos);
}
