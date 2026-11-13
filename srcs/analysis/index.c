/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaries <aaries@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 14:08:02 by aaries            #+#    #+#             */
/*   Updated: 2026/11/13 14:08:05 by aaries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	fill_tab(int *tab, t_stack *stack)
{
	t_node	*cur;
	int		i;

	if (!tab || !stack)
		return ;
	cur = stack->top;
	i = 0;
	while (cur)
	{
		tab[i] = cur->value;
		i++;
		cur = cur->next;
	}
}

static void	sort_tab(int *tab, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1)
		{
			if (tab[j] > tab[j + 1])
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	fill_index(int *tab, t_stack *stack)
{
	t_node	*cur;
	int		size;
	int		i;

	cur = stack->top;
	size = stack->size;
	while (cur)
	{
		i = 0;
		while (i < size)
		{
			if (cur->value == tab[i])
			{
				cur->index = i;
				break ;
			}
			i++;
		}
		cur = cur->next;
	}
}

int	assign_index(t_stack *stack)
{
	int	*tab;

	if (!stack)
		return (0);
	if (stack->size < 1)
		return (1);
	tab = malloc(sizeof(int) * stack->size);
	if (!tab)
		return (0);
	fill_tab(tab, stack);
	sort_tab(tab, stack->size);
	fill_index(tab, stack);
	free(tab);
	return (1);
}
