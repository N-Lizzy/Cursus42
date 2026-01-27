/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:50:32 by aruiznav          #+#    #+#             */
/*   Updated: 2026/01/26 11:33:33 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_stack **dest, t_stack **src)
{
	t_stack	*head;

	if (!(*src))
		return ;
	head = (*src);
	(*src) = (*src)->next;
	head->next = (*dest);
	(*dest) = head;
}

void	push_a(t_data *data)
{
	push(&data->a, &data->b);
	ft_printf("pa\n");
}

void	push_b(t_data *data)
{
	push(&data->b, &data->a);
	ft_printf("pb\n");
}
