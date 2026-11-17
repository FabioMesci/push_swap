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

static void	put_nbr(int n, int fd)
{
	char	c;

	if (n >= 10)
		put_nbr(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

static void	put_str(const char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

static void	put_percent(double disorder, int fd)
{
	int	hundredths;

	hundredths = (int)(disorder * 10000 + 0.5);
	put_nbr(hundredths / 100, fd);
	write(fd, ".", 1);
	if (hundredths % 100 < 10)
		write(fd, "0", 1);
	put_nbr(hundredths % 100, fd);
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
	put_str("[bench]", 2);
	while (from <= to)
	{
		put_str(" ", 2);
		put_str(op_name(from), 2);
		put_str(": ", 2);
		put_nbr(p->ops[from], 2);
		from++;
	}
	put_str("\n", 2);
}

void	print_bench(t_ps *p)
{
	int	total;
	int	i;

	total = 0;
	i = 0;
	while (i < OP_COUNT)
		total += p->ops[i++];
	put_str("[bench] disorder: ", 2);
	put_percent(p->disorder, 2);
	put_str("\n[bench] strategy: ", 2);
	put_str(p->strategy + 2, 2);
	put_str(" / ", 2);
	put_str(complexity(p), 2);
	put_str("\n[bench] total_ops: ", 2);
	put_nbr(total, 2);
	put_str("\n", 2);
	put_ops(p, OP_SA, OP_PB);
	put_ops(p, OP_RA, OP_RRR);
}
