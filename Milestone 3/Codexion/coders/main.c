/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 17:10:57 by aruiznav          #+#    #+#             */
/*   Updated: 2026/09/22 11:07:31 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	run_simulation_2(t_hub *hub, int i)
{
	hub->status = 1;
	pthread_cond_broadcast(&hub->scond);
	while (--i >= 0)
		pthread_join(hub->threads[i], NULL);
	return (1);
}

int	run_simulation(t_hub *hub)
{
	int	i;

	i = 0;
	while (i < hub->num_coders)
	{
		if (pthread_create(&hub->threads[i], NULL,
				&coder_routine, &hub->coders[i]))
			run_simulation_2(hub, i);
		i++;
	}
	if (pthread_create(&hub->monitor, NULL, &monitor_routine, hub))
	{
		hub->status = 1;
		pthread_cond_broadcast(&hub->scond);
		i = hub->num_coders;
		while (--i >= 0)
			pthread_join(hub->threads[i], NULL);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_hub	hub;
	int		i;

	if (argc != 9)
		return (1);
	if (set_hub(&hub, argv))
		return (1);
	hub.htime = get_time(0);
	if (run_simulation(&hub))
	{
		destroy_hub(&hub);
		return (1);
	}
	pthread_join(hub.monitor, NULL);
	i = 0;
	while (i < hub.num_coders)
	{
		pthread_join(hub.threads[i], NULL);
		i++;
	}
	destroy_hub(&hub);
	return (0);
}
