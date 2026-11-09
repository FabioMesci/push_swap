/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 10:23:56 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/09 16:24:54 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_atoi_safe(const char *str, int *out)
{
	int		i;
	int		signo;
	long	result;

	i = 0;
	signo = 1;
	result = 0;
	if (str[i] == '-')
		signo *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + (str[i] - '0');
		else
			return (0);
		if (result * signo > INT_MAX || result * signo < INT_MIN)
			return (0);
		i++;
	}
	*out = result * signo;
	return (1);
}

int	build_stack(t_stack *a, int argc, char **argv)
{
	int		i;
	int		n;
	t_node	*node;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi_safe(argv[i], &n) == 0)
			return (0);
		if (has_duplicate(a, n) == 1)
			return (0);
		node = new_node(n);
		if (node == NULL)
			return (0);
		stack_add_back(a, node);
		i++;
	}
	return (1);
}
