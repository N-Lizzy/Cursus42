/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 11:06:03 by aruiznav          #+#    #+#             */
/*   Updated: 2026/09/22 12:03:17 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	log_state(t_hub *hub, int id, char *msg)
{
	char	*color;

	color = "\033[0m";
	if (strcmp(msg, "is compiling") == 0)
		color = "\033[32m";
	else if (strcmp(msg, "has taken a dongle") == 0)
		color = "\033[33m";
	else if (strcmp(msg, "is debugging") == 0)
		color = "\033[34m";
	else if (strcmp(msg, "is refactoring") == 0)
		color = "\033[35m";
	else if (strcmp(msg, "burned out") == 0)
		color = "\033[31m";
	pthread_mutex_lock(&hub->wmutex);
	printf("%ld %d %s%s\033[0m\n",
		get_time(hub->htime), id, color, msg);
	pthread_mutex_unlock(&hub->wmutex);
}

int	set_hub_extra(t_hub *hub)
{
	if (set_heap(hub))
	{
		destroy_coders(hub, hub->num_coders);
		destroy_dongles(hub, hub->num_coders);
		free(hub->threads);
		return (1);
	}
	if (set_sync(hub))
	{
		free(hub->heap.data);
		destroy_coders(hub, hub->num_coders);
		destroy_dongles(hub, hub->num_coders);
		free(hub->threads);
		return (1);
	}
	return (0);
}

int	simulation_over(t_hub *hub)
{
	int	over;

	pthread_mutex_lock(&hub->smutex);
	over = hub->status;
	pthread_mutex_unlock(&hub->smutex);
	return (over);
}
