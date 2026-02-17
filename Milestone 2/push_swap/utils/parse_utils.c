/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:24:56 by aruiznav          #+#    #+#             */
/*   Updated: 2026/02/10 09:47:18 by aruiznav         ###   ########.fr       */
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
		if (!arg_split)
			error_free(data);
		while (arg_split[i])
		{
			if (!isnumber(arg_split[i]))
				error_free(data);
			add_back(&data->a, ft_atoi(arg_split[i]));
			i++;
		}
		free_split(arg_split);
	}
	else if (argc > 2)
	{
		error_free(data);
	}
}

void	add_back(t_stack **stack, int nb)
{
	t_stack	*new;
	t_stack	*tmp;

	if (isduplicate(*stack, nb))
		error_duplicated(*stack);
	new = malloc(sizeof(t_stack));
	if (!new)
		exit(1);
	new->nb = nb;
	new->next = NULL;
	if (!*stack)
	{
		*stack = new;
		return ;
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
	if (!nb || !nb[0])
		return (0);
	if (nb[i] == '-' || nb[i] == '+')
		i++;
	if (!nb[i])
		return (0);
	while (nb[i])
	{
		if (!ft_isdigit(nb[i]))
			return (0);
		i++;
	}
	return (1);
}

int	isduplicate(t_stack* stack, int nb)
{
	while (stack)
	{
		if (stack->nb == nb)
			return (1);
		stack = stack->next;
	}
	return (0);
}

