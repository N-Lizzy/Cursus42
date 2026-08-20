/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 17:56:59 by aruiznav          #+#    #+#             */
/*   Updated: 2026/08/20 17:57:31 by aruiznav         ###   ########.fr       */
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