/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:21:27 by aruiznav          #+#    #+#             */
/*   Updated: 2026/01/26 11:33:31 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	r_rotate(t_stack **stack)
{
	t_stack	*penultimate;
	t_stack	*last;

	if (!(*stack) || !(*stack)->next)
		return ;
	penultimate = (*stack);
	while (penultimate->next->next)
		penultimate = penultimate->next;
	last = penultimate->next;
	penultimate->next = NULL;
	last->next = (*stack);
	(*stack) = last;
}

void	r_rotate_a(t_data *data)
{
	r_rotate(&data->a);
	ft_printf("rra\n");
}

void	r_rotate_b(t_data *data)
{
	r_rotate(&data->b);
	ft_printf("rrb\n");
}

void	r_rotate_ab(t_data *data)
{
	r_rotate(&data->a);
	r_rotate(&data->b);
	ft_printf("rrr\n");
}
