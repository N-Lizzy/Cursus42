#include "push_swap.h"

void	radix_sort(t_data* data)
{
	int	i;
	int	j;
	int	size;
	int	max_bits;

	size = stack_size(data->a);
	max_bits = get_max_bits(data->a);
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			if (((data->a->nb >> i) & 1) == 1)
				rotate_a(data);
			else
				push_b(data);
			j++;
		}
		while (data->b)
			push_a(data);
		i++;
	}
}

int	get_max_bits(t_stack* stack)
{
	int	max;
	int	bits;

	max = 0;
	while (stack)
	{
		if (stack->nb > max)
			max = stack->nb;
		stack = stack->next;
	}
	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

void	index_stack(t_data* data)
{
	int* arr;
	int		size;
	t_stack* tmp;
	int		i;
	int		j;
	int		swap;

	size = stack_size(data->a);
	arr = stack_to_array(data->a, size);
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				swap = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = swap;
			}
			j++;
		}
		i++;
	}
	tmp = data->a;
	while (tmp)
	{
		i = 0;
		while (i < size)
		{
			if (tmp->nb == arr[i])
			{
				tmp->nb = i;
				break;
			}
			i++;
		}
		tmp = tmp->next;
	}
	free(arr);
}

int* stack_to_array(t_stack* a, int size)
{
	int* arr;
	int	i;

	arr = malloc(sizeof(int) * size);
	if (!arr)
		exit(1);
	i = 0;
	while (a)
	{
		arr[i++] = a->nb;
		a = a->next;
	}
	return (arr);
}



