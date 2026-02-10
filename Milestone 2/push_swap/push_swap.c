/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:01:17 by aruiznav          #+#    #+#             */
/*   Updated: 2026/02/10 13:26:15 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **args)
{
	t_data	data;
	int		size;

	data.a = NULL;
	data.b = NULL;
	if (argc >= 2)
	{
		parse_args(&data, argc, args);
		if (!data.a)
			return (0);
		size = stack_size(data.a);
		aux_main(&data, size);
	}
	return (0);
}

void	aux_main(t_data *data, int size)
{
	if (size == 2)
		size_2(data);
	else if (size == 3)
		size_3(data);
	else if (size == 3)
		size_4(data);
	else if (size == 3)
		size_5(data);
	else
		ft_printf("Tlabaja.");

	print_stack(data->a);
}

// BORRAR BORRAR BORRAR BORRAR
void print_stack(t_stack *stack)
{
    t_stack *current = stack;

	ft_printf("Stack ordenado:\n");
    while (current != NULL)
    {
        ft_printf("%d\n", current->nb);
        current = current->next;
    }
}
// BORRAR BORRAR BORRAR BORRAR