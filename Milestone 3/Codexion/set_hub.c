/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 16:23:26 by aruiznav          #+#    #+#             */
/*   Updated: 2026/09/02 19:35:55 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	set_coder(t_hub *hub, int i)
{
	hub->coders[i].id = i + 1;
	hub->coders[i].hub = hub;
	hub->coders[i].last_compile = 0;
	hub->coders[i].compiles = 0;
	hub->coders[i].state = ST_IDLE;
	if (!i)
		hub->coders[i].left_dongle = &hub->dongles[hub->num_coders - 1];
	else
		hub->coders[i].left_dongle = &hub->dongles[i - 1];
	hub->coders[i].right_dongle = &hub->dongles[i];
	if (pthread_mutex_init(&hub->coders[i].cmutex, NULL))
	{
		destroy_coders(hub, i);
		return (1);
	}
	return (0);
}

int	set_coders(t_hub *hub)
{
	int	i;

	hub->coders = malloc(sizeof(t_coder) * hub->num_coders);
	if (!hub->coders)
		return (1);
	i = 0;
	while (i < hub->num_coders)
	{
		if (set_coder(hub, i))
		{
			destroy_coders(hub, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	set_dongles(t_hub *hub)
{
	int	i;

	i = 0;
	hub->dongles = malloc(hub->num_coders * sizeof(t_dongle));
	if (!hub->dongles)
		return (1);
	while (i < hub->num_coders)
	{
		hub->dongles[i].is_taken = 0;
		hub->dongles[i].last_used = -hub->tcooldown;
		if (pthread_mutex_init(&hub->dongles[i].dmutex, NULL))
		{
			destroy_dongles(hub, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	set_arg(t_hub *hub, char **argv)
{
	if (check_numarg(argv[1]) || check_numarg(argv[2]) || check_numarg(argv[3])
		|| check_numarg(argv[4]) || check_numarg(argv[5])
		|| check_numarg(argv[6]) || check_numarg(argv[7]))
		return (1);
	hub->num_coders = atoi(argv[1]);
	hub->tburnout = atoi(argv[2]);
	hub->tcompile = atoi(argv[3]);
	hub->tdebug = atoi(argv[4]);
	hub->trefactor = atoi(argv[5]);
	hub->max_compiles = atoi(argv[6]);
	hub->tcooldown = atoi(argv[7]);
	hub->scheduler = check_scheduler(argv[8]);
	if (hub->num_coders > 500 || !hub->num_coders || !hub->tburnout
		|| !hub->tcompile || !hub->tdebug || !hub->trefactor
		|| !hub->max_compiles || !hub->tcooldown || !hub->scheduler)
		return (1);
	hub->status = 0;
	hub->request_order = 0;
	return (0);
}

int	set_hub(t_hub *hub, char **argv)
{
	if (set_arg(hub, argv))
		return (1);
	if (set_dongles(hub))
		return (1);
	if (set_coders(hub))
	{
		destroy_dongles(hub, hub->num_coders);
		return (1);
	}
	hub->threads = malloc(hub->num_coders * sizeof(pthread_t));
	if (!hub->threads)
	{
		destroy_coders(hub, hub->num_coders);
		destroy_dongles(hub, hub->num_coders);
		return (1);
	}
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
