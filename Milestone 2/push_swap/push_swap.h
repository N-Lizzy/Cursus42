/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:56:32 by aruiznav          #+#    #+#             */
/*   Updated: 2026/02/10 13:22:22 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

typedef struct s_stack
{
	long			nb;
	struct s_stack	*next;
}	t_stack;

typedef struct s_data
{
	t_stack	*a;
	t_stack	*b;
}	t_data;

// BORRAR BORRAR BORRAR BORRAR
void print_stack(t_stack *stack);
// BORRAR BORRAR BORRAR BORRAR

void	aux_main(t_data *data, int size);

// Operations
void	swap(t_stack **stack);
void	swap_a(t_data *d);
void	swap_b(t_data *d);
void	swap_ab(t_data *d);
void	push(t_stack **dest, t_stack **src);
void	push_a(t_data *d);
void	push_b(t_data *d);
void	rotate(t_stack **stack);
void	rotate_a(t_data *d);
void	rotate_b(t_data *d);
void	rotate_ab(t_data *d);
void	r_rotate(t_stack **stack);
void	r_rotate_a(t_data *d);
void	r_rotate_b(t_data *d);
void	r_rotate_ab(t_data *d);

// Parse
void	parse_args(t_data *data, int argc, char **args);
void	add_back(t_stack **stack, int nb);
int		isnumber(char *nb);

int		stack_size(t_stack *stack);

// Sort
void	size_2(t_data *data);
void	size_3(t_data *data);
void	size_4(t_data* data);
void	size_5(t_data* data);

// Free
void	free_split(char **split);
void	free_list(t_stack **stack);
void	error_free(t_data *data);

#endif