/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:01:17 by aruiznav          #+#    #+#             */
/*   Updated: 2026/02/25 12:12:15 by aruiznav         ###   ########.fr       */
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
		free_list(&data.a);
		free_list(&data.b);
	}
	else
		ft_printf("Error \n");
	return (0);
}

void	aux_main(t_data *data, int size)
{
	if (is_sorted(data->a))
		return ;
	if (size == 2)
		size_2(data);
	else if (size == 3)
		size_3(data);
	else if (size == 4)
		size_4(data);
	else if (size == 5)
		size_5(data);
	else
	{
		index_stack(data);
		radix_sort(data);
	}
}
