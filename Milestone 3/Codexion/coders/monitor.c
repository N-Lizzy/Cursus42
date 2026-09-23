/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 10:53:41 by aruiznav          #+#    #+#             */
/*   Updated: 2026/09/22 12:02:23 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	all_compiled(t_hub *hub)
{
	int	i;
	int	ret;

	ret = 1;
	i = 0;
	while (i < hub->num_coders)
	{
		pthread_mutex_lock(&hub->coders[i].cmutex);
		if (hub->coders[i].compiles < hub->max_compiles)
			ret = 0;
		pthread_mutex_unlock(&hub->coders[i].cmutex);
		if (!ret)
			return (0);
		i++;
	}
	return (1);
}

static int	someone_burned(t_hub *hub, long now)
{
	int	i;
	int	burned;

	i = 0;
	while (i < hub->num_coders)
	{
		burned = 0;
		pthread_mutex_lock(&hub->coders[i].cmutex);
		if (hub->coders[i].compiles < hub->max_compiles
			&& hub->coders[i].state != ST_COMPILE
			&& now - hub->coders[i].last_compile >= hub->tburnout)
			burned = 1;
		pthread_mutex_unlock(&hub->coders[i].cmutex);
		if (burned)
		{
			log_state(hub, hub->coders[i].id, "burned out");
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_hub	*hub;
	long	now;

	hub = (t_hub *)arg;
	pthread_mutex_lock(&hub->smutex);
	while (!hub->status)
	{
		pthread_mutex_unlock(&hub->smutex);
		now = get_time(hub->htime);
		if (someone_burned(hub, now) || all_compiled(hub))
		{
			pthread_mutex_lock(&hub->smutex);
			hub->status = 1;
			pthread_cond_broadcast(&hub->scond);
			pthread_mutex_unlock(&hub->smutex);
			break ;
		}
		usleep(200);
		pthread_mutex_lock(&hub->smutex);
	}
	return (NULL);
}
