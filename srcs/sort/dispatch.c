/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:09:44 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/13 09:11:41 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	dispatch(t_ps *p)
{
	if (p->a.size <= 5)
		sort_small(p);
	else if (ft_strcmp(p->strategy, "--simple") == 0)
		sort_simple(p);
}
