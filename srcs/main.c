/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 12:07:00 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/12 18:03:06 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	free_all(t_ps *p)
{
	free_stack(&p->a);
	free_stack(&p->b);
}

static int	exit_with_error(t_ps *p)
{
	free_all(p);
	write(2, "Error\n", 6);
	return (1);
}

static void	execute(t_ps *p)
{
	if (check_if_sorted(&p->a) == 0)
		dispatch(p);
}

int	main(int argc, char **argv)
{
	t_ps	p;
	int		start;

	ft_bzero(&p, sizeof(p));
	start = parse_flags(argc, argv, &p);
	if (start == -1)
		return (exit_with_error(&p));
	if (start == argc)
		return (0);
	if (p.strategy == NULL)
		p.strategy = "--adaptive";
	if (build_stack(&p.a, argc, argv, start) == 0)
		return (exit_with_error(&p));
	execute(&p);
	free_all(&p);
	return (0);
}
