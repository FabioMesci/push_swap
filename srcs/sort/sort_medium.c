/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaries <aaries@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 16:16:54 by aaries            #+#    #+#             */
/*   Updated: 2026/11/18 16:37:04 by aaries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	chunk_size(int n)
{
	int	root;

	root = 1;
	while (root * root < n)
		root++;
	return (root * 3 / 2);
}

static void	push_chunks(t_ps *p, int size)
{
	int	pushed;

	pushed = 0;
	while (p->a.top != NULL)
	{
		if (p->a.top->index < pushed + size)
		{
			pb(p);
			if (p->b.top->index < pushed)
				rb(p);
			pushed++;
		}
		else
			ra(p);
	}
}

static int	max_pos(t_stack *s)
{
	t_node	*cur;
	int		pos;
	int		max_p;
	int		max;

	cur = s->top;
	max = cur->index;
	pos = 0;
	max_p = 0;
	while (cur != NULL)
	{
		if (cur->index > max)
		{
			max = cur->index;
			max_p = pos;
		}
		pos++;
		cur = cur->next;
	}
	return (max_p);
}

static void	push_max(t_ps *p)
{
	int	pos;
	int	size;

	size = p->b.size;
	pos = max_pos(&p->b);
	if (pos <= size - pos)
	{
		while (pos-- > 0)
			rb(p);
	}
	else
	{
		while (pos++ < size)
			rrb(p);
	}
	pa(p);
}

void	sort_medium(t_ps *p)
{
	if (check_if_sorted(&p->a))
		return ;
	push_chunks(p, chunk_size(p->a.size));
	while (p->b.top != NULL)
		push_max(p);
}
