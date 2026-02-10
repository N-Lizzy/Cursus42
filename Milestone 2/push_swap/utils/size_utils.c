/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:00:13 by aruiznav          #+#    #+#             */
/*   Updated: 2026/02/10 13:26:42 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	size_2(t_data *data)
{
	if (!data->a || !data->a->next)
		return ;
	if ((data->a->nb) > (data->a->next->nb))
		swap_a(data);
}

void	size_3(t_data *data)
{
	long	a;
	long	b;
	long	c;
	
	if (!data->a || !data->a->next || !data->a->next->next)
		return ;
	a = data->a->nb;
	b = data->a->next->nb;
	c = data->a->next->next->nb;
	if (a > b && b < c && a < c)
		swap_a(data);
	else if (a > b && b < c && a > c)
		rotate_a(data);
	else if (a > b && b > c)
	{
		swap_a(data);
		r_rotate_a(data);
	}
	else if (a < b && b > c && a < c)
	{
		swap_a(data);
		rotate_a(data);
	}
	else if (a < b && b > c && a > c)
		r_rotate_a(data);
}

void	size_4(t_data *data)
{
	
}

void	size_5(t_data *data)
{
	
}
