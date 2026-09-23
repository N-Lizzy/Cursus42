/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 17:56:59 by aruiznav          #+#    #+#             */
/*   Updated: 2026/09/02 19:35:44 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_dongles(t_hub *hub, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&hub->dongles[i].dmutex);
	free(hub->dongles);
}

void	destroy_coders(t_hub *hub, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&hub->coders[i].cmutex);
	free(hub->coders);
}

void	destroy_hub(t_hub *hub)
{
	pthread_mutex_destroy(&hub->smutex);
	pthread_mutex_destroy(&hub->wmutex);
	pthread_cond_destroy(&hub->scond);
	free(hub->heap.data);
	destroy_coders(hub, hub->num_coders);
	destroy_dongles(hub, hub->num_coders);
	free(hub->threads);
}
