/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 17:10:57 by aruiznav          #+#    #+#             */
/*   Updated: 2026/09/02 19:00:50 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	EN ESTE ORDEN:
	number_of_coders -> numero personas
	time_to_burnout -> tiempo antes de morir
	time_to_compile -> tiempo para compilar
	time_to_debug -> tiempo para debuggear
	time_to_refactor -> tiempo para refactorizar
	number_of_compiles_required -> numero de compilaciones TODOS tienen que hacerlas
	dongle_cooldown -> tiempo de cooldown del dongle
	scheduler -> fifo o edf
			fifo -> el dongle se concede por orden de llegada
			edf -> el dongle se concede al que tenga menos tiempo para burnout
				(last_compile_start + time_to_burnout)
*/

#include "codexion.h"

static int	run_simulation(t_hub *hub)
{
	int	i;

	i = 0;
	while (i < hub->num_coders)
	{
		if (pthread_create(&hub->threads[i], NULL, &coder_routine,
				&hub->coders[i]))
		{
			hub->status = 1;
			pthread_cond_broadcast(&hub->scond);
			while (--i >= 0)
				pthread_join(hub->threads[i], NULL);
			return (1);
		}
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


