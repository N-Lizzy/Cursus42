/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 19:18:07 by aruiznav          #+#    #+#             */
/*   Updated: 2026/09/02 19:49:45 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	set_sync(t_hub *hub)
{
	if (pthread_mutex_init(&hub->smutex, NULL))
		return (1);
	if (pthread_mutex_init(&hub->wmutex, NULL))
	{
		pthread_mutex_destroy(&hub->smutex);
		return (1);
	}
	if (pthread_cond_init(&hub->scond, NULL))
	{
		pthread_mutex_destroy(&hub->smutex);
		pthread_mutex_destroy(&hub->wmutex);
		return (1);
	}
	return (0);
}

int	set_heap(t_hub *hub)
{
	hub->heap.size = 0;
	hub->heap.capacity = hub->num_coders;
	hub->heap.data = malloc(sizeof(t_request) * hub->heap.capacity);
	if (!hub->heap.data)
		return (1);
	return (0);
}

int	heap_push(t_hub *hub, t_request request)
{
	int	index;
	int	parent;

	if (hub->heap.size >= hub->heap.capacity)
		return (1);
	index = hub->heap.size;
	hub->heap.data[index] = request;
	hub->heap.size++;
	while (index > 0)
	{
		parent = (index - 1) / 2;
		if (!request_before(hub,
				&hub->heap.data[index],
				&hub->heap.data[parent]))
			break ;
		swap_request(&hub->heap.data[index],
			&hub->heap.data[parent]);
		index = parent;
	}
	return (0);
}

int	heap_pop(t_hub *hub, t_request *request)
{
	int	index;
	int	left;
	int	right;
	int	best;

	if (hub->heap.size == 0)
		return (1);
	*request = hub->heap.data[0];
	hub->heap.size--;
	if (hub->heap.size == 0)
		return (0);
	hub->heap.data[0] = hub->heap.data[hub->heap.size];
	index = 0;
	while (1)
	{
		left = index * 2 + 1;
		right = index * 2 + 2;
		if (left >= hub->heap.size)
			break ;
		best = left;
		if (right < hub->heap.size
			&& request_before(hub,
				&hub->heap.data[right],
				&hub->heap.data[left]))
			best = right;
		if (!request_before(hub,
				&hub->heap.data[best],
				&hub->heap.data[index]))
			break ;
		swap_request(&hub->heap.data[index],
			&hub->heap.data[best]);
		index = best;
	}
	return (0);
}
