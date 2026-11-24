/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaries <aaries@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 18:11:41 by aaries            #+#    #+#             */
/*   Updated: 2026/11/17 18:42:05 by aaries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	put_percent(double disorder, int fd)
{
	int	hundredths;

	hundredths = (int)(disorder * 10000 + 0.5);
	ft_putnbr_fd(hundredths / 100, fd);
	write(fd, ".", 1);
	if (hundredths % 100 < 10)
		write(fd, "0", 1);
	ft_putnbr_fd(hundredths % 100, fd);
	write(fd, "%", 1);
}

static const char	*complexity(t_ps *p)
{
	if (ft_strcmp(p->strategy, "--simple") == 0)
		return ("O(n^2)");
	if (ft_strcmp(p->strategy, "--medium") == 0)
		return ("O(n\xe2\x88\x9an)");
	if (ft_strcmp(p->strategy, "--complex") == 0)
		return ("O(n log n)");
	if (p->disorder < 0.2)
		return ("O(n)");
	if (p->disorder < 0.5)
		return ("O(n\xe2\x88\x9an)");
	return ("O(n log n)");
}

static void	put_ops(t_ps *p, int from, int to)
{
	ft_putstr_fd("[bench]", 2);
	while (from <= to)
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(op_name(from), 2);
		ft_putstr_fd(": ", 2);
		ft_putnbr_fd(p->ops[from], 2);
		from++;
	}
	ft_putstr_fd("\n", 2);
}

void	print_bench(t_ps *p)
{
	int	total;
	int	i;

	total = 0;
	i = 0;
	while (i < OP_COUNT)
		total += p->ops[i++];
	ft_putstr_fd("[bench] disorder: ", 2);
	put_percent(p->disorder, 2);
	ft_putstr_fd("\n[bench] strategy: ", 2);
	ft_putstr_fd(p->strategy + 2, 2);
	ft_putstr_fd(" / ", 2);
	ft_putstr_fd(complexity(p), 2);
	ft_putstr_fd("\n[bench] total_ops: ", 2);
	ft_putnbr_fd(total, 2);
	ft_putstr_fd("\n", 2);
	put_ops(p, OP_SA, OP_PB);
	put_ops(p, OP_RA, OP_RRR);
}
