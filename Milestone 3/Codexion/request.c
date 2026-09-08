/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 19:49:33 by aruiznav          #+#    #+#             */
/*   Updated: 2026/09/02 19:51:18 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_request	make_request(t_hub *hub, t_coder *coder)
{
	t_request	request;

	request.coder = coder;
	request.order = hub->request_order++;
	request.deadline = coder->last_compile + hub->tburnout;
	return (request);
}

int	request_compile(t_coder *coder)
{
	t_hub		*hub;
	t_request	request;

	hub = coder->hub;
	pthread_mutex_lock(&hub->smutex);
	request = make_request(hub, coder);
	if (heap_push(hub, request))
	{
		pthread_mutex_unlock(&hub->smutex);
		return (1);
	}
	pthread_cond_broadcast(&hub->scond);
	pthread_mutex_unlock(&hub->smutex);
	return (0);
}

int	is_my_turn(t_coder *coder)
{
	t_hub		*hub;

	hub = coder->hub;
	if (hub->heap.size == 0)
		return (0);
	return (hub->heap.data[0].coder == coder);
}

int	take_turn(t_coder *coder)
{
	t_hub		*hub;
	t_request	request;

	hub = coder->hub;
	pthread_mutex_lock(&hub->smutex);
	while (!is_my_turn(coder) && !hub->status)
		pthread_cond_wait(&hub->scond, &hub->smutex);
	if (hub->status)
	{
		pthread_mutex_unlock(&hub->smutex);
		return (1);
	}
	heap_pop(hub, &request);
	pthread_cond_broadcast(&hub->scond);
	pthread_mutex_unlock(&hub->smutex);
	return (0);
}
