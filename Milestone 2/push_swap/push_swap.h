/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 10:56:32 by aruiznav          #+#    #+#             */
/*   Updated: 2026/02/24 12:52:37 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

typedef struct s_stack
{
	int				nb;
	struct s_stack	*next;
}	t_stack;

typedef struct s_data
{
	t_stack	*a;
	t_stack	*b;
}	t_data;

void	aux_main(t_data *data, int size);

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

void	size_2(t_data *data);
void	size_3(t_data *data);
void	size_4(t_data *data);
void	size_5(t_data *data);
void	radix_sort(t_data *data);

void	parse_args(t_data *data, int argc, char **args);
void	add_back(t_stack **stack, int nb, char **split);
int		isnumber(char *nb);
int		isduplicate(t_stack *stack, int nb);
int		is_valid_int(char *str);
int		stack_size(t_stack *stack);
int		get_max_bits(t_stack *stack);
void	sort_array(int *arr, int size);
void	assign_indexes(t_stack *stack, int *arr, int size);
void	index_stack(t_data *data);
int		*stack_to_array(t_stack *a, int size);
int		find_min_pos(t_stack *a);
void	move_to_top_a(t_data *data, int pos, int size);
int		is_sorted(t_stack *a);

void	free_split(char **split);
void	free_list(t_stack **stack);
void	error_free(t_data *data);
void	error_duplicated(t_stack **stack, char **split);

#endif