/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 11:44:14 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/09 14:24:50 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*new_node(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->value = value;
	node->index = 0;
	node->next = NULL;
	return (node);
}

void	stack_add_back(t_stack *stack, t_node *node)
{
	t_node	*cur;

	if (stack == NULL || node == NULL)
		return ;
	if (stack->top == NULL)
		stack->top = node;
	else
	{
		cur = stack->top;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = node;
	}
	stack->size = stack->size + 1;
}

int	has_duplicate(t_stack *stack, int value)
{
	t_node	*cur;

	if (stack == NULL)
		return (0);
	cur = stack->top;
	while (cur)
	{
		if (cur->value == value)
			return (1);
		cur = cur->next;
	}
	return (0);
}

void	free_stack(t_stack *stack)
{
	t_node	*cur;
	t_node	*tmp;

	if (stack == NULL)
		return ;
	cur = stack->top;
	while (cur)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	stack->top = NULL;
	stack->size = 0;
}
