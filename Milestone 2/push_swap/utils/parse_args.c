/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:24:56 by aruiznav          #+#    #+#             */
/*   Updated: 2026/01/27 11:12:28 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	parse_args(t_data *data, int argc, char **args)
{
	char	**arg_split;
	int		i;

	i = 0;
	
	if (argc == 2)
	{
		arg_split = ft_split(args[1], ' ');
		if(!arg_split)
			error_free(data);
		while (arg_split[i])
		{
			if (!isnumber(arg_split[i]))
				error_free(data);
			add_back(&data->a, ft_atoi(arg_split[i]));
			i++;
		}
		
		
		i = 0;
		t_stack	*current = data->a;
		while (current)
		{
			ft_printf("nodo[%d] = %d\n", i, current->nb);
			current = current->next;
			i++;
		}
	}
	else
		error_free(data);
}

void	add_back(t_stack **stack, int nb)
{
	t_stack *new;
	t_stack *tmp;

	new = malloc(sizeof(t_stack));
	if (!new)
		exit(1);
	new->nb = nb;
	new->next = NULL;

	if (!*stack)
	{
		*stack = new;
		return;
	}
	tmp = *stack;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	isnumber(char *nb)
{
	int	i;

	i = 0;
	if(nb[0] == '-')
		i++;

	while(nb[i])
	{
		if(ft_isdigit(nb[i]))
			i++;
		else
			return (0);
	}
	return (1);
}



