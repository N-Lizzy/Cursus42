/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 19:49:33 by aruiznav          #+#    #+#             */
/*   Updated: 2026/09/22 12:10:03 by aruiznav         ###   ########.fr       */
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

static void	set_wait_time(struct timespec *ts)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ts->tv_sec = tv.tv_sec;
	ts->tv_nsec = tv.tv_usec * 1000 + 1000000;
	if (ts->tv_nsec >= 1000000000)
	{
		ts->tv_sec++;
		ts->tv_nsec -= 1000000000;
	}
}

int	take_turn(t_coder *coder)
{
	t_hub			*hub;
	t_request		request;
	struct timespec	ts;

	hub = coder->hub;
	pthread_mutex_lock(&hub->smutex);
	while (!hub->status)
	{
		if (is_my_turn(coder))
		{
			heap_pop(hub, &request);
			pthread_cond_broadcast(&hub->scond);
			pthread_mutex_unlock(&hub->smutex);
			while (!take_dongles(coder))
			{
				if (simulation_over(hub))
					return (1);
				usleep(100);
			}
			log_state(hub, coder->id, "has taken a dongle");
			if (coder->left_dongle != coder->right_dongle)
				log_state(hub, coder->id, "has taken a dongle");
			return (0);
		}
		set_wait_time(&ts);
		pthread_cond_timedwait(&hub->scond, &hub->smutex, &ts);
	}
	pthread_mutex_unlock(&hub->smutex);
	return (1);
}
