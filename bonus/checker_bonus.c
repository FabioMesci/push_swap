/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 18:49:09 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/25 19:56:32 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"

static int	apply_a(t_ps *p, char *l)
{
	if (ft_strcmp(l, "sa\n") == 0)
		sa(p);
	else if (ft_strcmp(l, "sb\n") == 0)
		sb(p);
	else if (ft_strcmp(l, "ss\n") == 0)
		ss(p);
	else if (ft_strcmp(l, "pa\n") == 0)
		pa(p);
	else if (ft_strcmp(l, "pb\n") == 0)
		pb(p);
	else
		return (0);
	return (1);
}

static int	apply_b(t_ps *p, char *l)
{
	if (ft_strcmp(l, "ra\n") == 0)
		ra(p);
	else if (ft_strcmp(l, "rb\n") == 0)
		rb(p);
	else if (ft_strcmp(l, "rr\n") == 0)
		rr(p);
	else if (ft_strcmp(l, "rra\n") == 0)
		rra(p);
	else if (ft_strcmp(l, "rrb\n") == 0)
		rrb(p);
	else if (ft_strcmp(l, "rrr\n") == 0)
		rrr(p);
	else
		return (0);
	return (1);
}

static int	read_ops(t_ps *p)
{
	char	*line;
	int		ok;

	ok = 1;
	line = get_next_line(0);
	while (line != NULL)
	{
		if (ok == 1)
			ok = apply_a(p, line) || apply_b(p, line);
		free(line);
		line = get_next_line(0);
	}
	return (ok);
}

int	main(int argc, char **argv)
{
	t_ps	p;

	if (argc < 2)
		return (0);
	ft_bzero(&p, sizeof(p));
	p.silent = 1;
	if (build_stack(&p.a, argc, argv, 1) == 0 || read_ops(&p) == 0)
	{
		ft_putstr_fd("Error\n", 2);
		free_stack(&p.a);
		free_stack(&p.b);
		return (1);
	}
	if (check_if_sorted(&p.a) == 1 && p.b.size == 0)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
	free_stack(&p.a);
	free_stack(&p.b);
	return (0);
}
