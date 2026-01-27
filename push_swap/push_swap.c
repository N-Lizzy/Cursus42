/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:01:17 by aruiznav          #+#    #+#             */
/*   Updated: 2026/01/23 13:00:54 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **args)
{
	t_data	data;
	
	data.a = NULL;
	data.b = NULL;
	if (argc >= 2)
	{
		parse_args(&data, argc, args);
		if (!data.a)
			return (0);
	}
	return (0);
}