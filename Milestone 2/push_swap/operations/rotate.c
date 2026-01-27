/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:28:56 by aruiznav          #+#    #+#             */
/*   Updated: 2026/01/26 11:33:30 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_stack **stack)
{
	t_stack	*first;
	t_stack	*last;

	if (!stack || !(*stack) || !(*stack)->next)
		return ;
	first = (*stack);
	(*stack) = (*stack)->next;
	last = *stack;
	while (last->next)
		last = last->next;
	first->next = NULL;
	last->next = first;
}

void	rotate_a(t_data *data)
{
	rotate(&data->a);
	ft_printf("ra\n");
}

void	rotate_b(t_data *data)
{
	rotate(&data->b);
	ft_printf("rb\n");
}

void	rotate_ab(t_data *data)
{
	rotate(&data->a);
	rotate(&data->b);
	ft_printf("rr\n");
}
