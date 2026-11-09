/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 12:07:00 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/09 16:32:41 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_ps	p;

	if (argc < 2)
		return (0);
	ft_bzero(&p, sizeof(p));
	if (build_stack(&p.a, argc, argv) == 0)
	{
		free_stack(&p.a);
		write(2, "Error\n", 6);
		return (1);
	}
	free_stack(&p.a);
	return (0);
}
