/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 16:23:32 by aruiznav          #+#    #+#             */
/*   Updated: 2026/09/22 13:18:47 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time(long start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
}

int	check_numarg(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

char	*check_scheduler(char *argv)
{
	if ((strcmp(argv, "fifo") == 0) || (strcmp(argv, "edf") == 0))
		return (argv);
	return (NULL);
}

int	request_before(t_hub *hub, t_request *a, t_request *b)
{
	if (strcmp(hub->scheduler, "fifo") == 0)
		return (a->order < b->order);
	if (a->deadline != b->deadline)
		return (a->deadline < b->deadline);
	return (a->order < b->order);
}

void	swap_request(t_request *a, t_request *b)
{
	t_request	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
