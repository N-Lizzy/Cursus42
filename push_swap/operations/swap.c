/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:00:19 by aruiznav          #+#    #+#             */
/*   Updated: 2026/01/26 11:33:28 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack **stack)
{
	t_stack	*temp;

	if (!(*stack) || !((*stack)->next))
		return ;
	temp = (*stack);
	*stack = (*stack)->next;
	temp->next = (*stack)->next;
	(*stack)->next = temp;
}

void	swap_a(t_data *data)
{
	swap(&data->a);
	ft_printf("sa\n");
}

void	swap_b(t_data *data)
{
	swap(&data->b);
	ft_printf("sb\n");
}

void	swap_ab(t_data *data)
{
	swap(&data->a);
	swap(&data->b);
	ft_printf("ss\n");
}
