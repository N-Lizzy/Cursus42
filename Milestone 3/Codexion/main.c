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

int	main(int argc, char **argv)
{
	t_hub	hub;
	int		i;

	i = 0;
	if (argc != 9)
		return (1);
	if (set_hub(&hub, argv))
		return (1);
	hub.htime = get_time(0);
	while (i < hub.num_coders)
	{
		//if(pthread_create(&hub.threads[i], NULL, &coder_routine, &hub.coders[i]))
			// Return limpieza
		i++;
	}
	// Checkeo
	i = 0;
	while(i < hub.num_coders)
	{
		if(pthread_join(hub.threads[i], NULL))
		i++;
	}
	// Limpieza
	return (0);
}
