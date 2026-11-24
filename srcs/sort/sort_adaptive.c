/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_adaptive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaries <aaries@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 16:27:38 by aaries            #+#    #+#             */
/*   Updated: 2026/11/23 17:53:44 by aaries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_adaptive(t_ps *p)
{
	if (p->disorder < 0.2)
		sort_simple(p);
	else if (p->disorder < 0.5)
		sort_medium(p);
	else
		sort_complex(p);
}
