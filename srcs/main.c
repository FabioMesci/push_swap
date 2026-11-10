/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 12:07:00 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/10 14:17:11 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_ps	p;
	int		start;

	ft_bzero(&p, sizeof(p));
	start = parse_flags(argc, argv, &p);
	if (start == -1)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (start == argc)
		return (0);
	if (p.strategy == NULL)
		p.strategy = "--adaptive";
	if (build_stack(&p.a, argc, argv, start) == 0)
	{
		free_stack(&p.a);
		write(2, "Error\n", 6);
		return (1);
	}
	free_stack(&p.a);
	return (0);
}
