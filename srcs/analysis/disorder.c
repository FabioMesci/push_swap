/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaries <aaries@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 13:06:03 by aaries            #+#    #+#             */
/*   Updated: 2026/11/17 17:06:59 by aaries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double	compute_disorder(t_stack *a)
{
	int		pairs;
	int		invert;
	t_node	*i;
	t_node	*j;

	i = a->top;
	pairs = 0;
	invert = 0;
	while (i)
	{
		j = i->next;
		while (j)
		{
			pairs++;
			if (i->value > j->value)
				invert++;
			j = j->next;
		}
		i = i->next;
	}
	if (pairs == 0)
		return (0);
	return ((double)invert / pairs);
}
