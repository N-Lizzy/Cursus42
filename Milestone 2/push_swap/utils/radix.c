/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:12:49 by aruiznav          #+#    #+#             */
/*   Updated: 2026/02/20 12:15:50 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	radix_sort(t_data *data)
{
	int	i;
	int	j;
	int	size;
	int	max_bits;

	size = stack_size(data->a);
	max_bits = get_max_bits(data->a);
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			if (((data->a->nb >> i) & 1) == 1)
				rotate_a(data);
			else
				push_b(data);
			j++;
		}
		while (data->b)
			push_a(data);
		i++;
	}
}

int	get_max_bits(t_stack *stack)
{
	int	max;
	int	bits;

	max = 0;
	while (stack)
	{
		if (stack->nb > max)
			max = stack->nb;
		stack = stack->next;
	}
	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

void	sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	swap;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				swap = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = swap;
			}
			j++;
		}
		i++;
	}
}

void	assign_indexes(t_stack *stack, int *arr, int size)
{
	t_stack	*tmp;
	int		i;

	tmp = stack;
	while (tmp)
	{
		i = 0;
		while (i < size)
		{
			if (tmp->nb == arr[i])
			{
				tmp->nb = i;
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
}

void	index_stack(t_data *data)
{
	int		*arr;
	int		size;

	size = stack_size(data->a);
	arr = stack_to_array(data->a, size);
	sort_array(arr, size);
	assign_indexes(data->a, arr, size);
	free(arr);
}
