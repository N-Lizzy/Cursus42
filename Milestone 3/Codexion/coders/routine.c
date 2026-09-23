/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 10:53:48 by aruiznav          #+#    #+#             */
/*   Updated: 2026/09/22 13:18:24 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*coder_routine(void *arg)
{
	t_coder	*coder;
	t_hub	*hub;

	coder = (t_coder *)arg;
	hub = coder->hub;
	while (!simulation_over(hub) && coder->compiles < hub->max_compiles)
	{
		if (request_compile(coder) || take_turn(coder))
			break ;
		pthread_mutex_lock(&coder->cmutex);
		coder->state = ST_COMPILE;
		coder->last_compile = get_time(hub->htime);
		pthread_mutex_unlock(&coder->cmutex);
		log_state(hub, coder->id, "is compiling");
		usleep(hub->tcompile * 1000);
		release_dongles(coder);
		pthread_mutex_lock(&coder->cmutex);
		coder->compiles++;
		coder->state = ST_DEBUG;
		pthread_mutex_unlock(&coder->cmutex);
		log_state(hub, coder->id, "is debugging");
		usleep(hub->tdebug * 1000);
		pthread_mutex_lock(&coder->cmutex);
		coder->state = ST_REFACTOR;
		pthread_mutex_unlock(&coder->cmutex);
		log_state(hub, coder->id, "is refactoring");
		usleep(hub->trefactor * 1000);
	}
	return (NULL);
}
