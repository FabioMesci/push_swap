/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:21:41 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/11 15:51:42 by fmesci           ###   ########.fr       */
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
