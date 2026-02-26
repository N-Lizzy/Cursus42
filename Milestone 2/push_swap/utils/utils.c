/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:56:07 by aruiznav          #+#    #+#             */
/*   Updated: 2026/02/24 10:44:49 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	stack_size(t_stack *stack)
{
	int	i;

	i = 0;
	if (!stack)
		return (0);
	while (stack)
	{
		stack = stack->next;
		i++;
	}
	return (i);
}

int	find_min_pos(t_stack *a)
{
	int		pos;
	int		min_pos;
	int		min;

	pos = 0;
	min_pos = 0;
	min = a->nb;
	while (a)
	{
		if (a->nb < min)
		{
			min = a->nb;
			min_pos = pos;
		}
		a = a->next;
		pos++;
	}
	return (min_pos);
}

void	move_to_top_a(t_data *data, int pos, int size)
{
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			rotate_a(data);
	}
	else
	{
		while (pos++ < size)
			r_rotate_a(data);
	}
}

int	is_sorted(t_stack *a)
{
	while (a && a->next)
	{
		if (a->nb > a->next->nb)
			return (0);
		a = a->next;
	}
	return (1);
}

int	*stack_to_array(t_stack *a, int size)
{
	int		*arr;
	int		i;

	arr = malloc(sizeof(int) * size);
	if (!arr)
		exit(1);
	i = 0;
	while (a)
	{
		arr[i++] = a->nb;
		a = a->next;
	}
	return (arr);
}
