/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 17:10:48 by aruiznav          #+#    #+#             */
/*   Updated: 2026/08/18 17:58:48 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>

typedef struct s_dongle
{
	int				is_taken;
	long			last_used;
	pthread_mutex_t	dmutex;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	struct s_hub	*hub;
	long			last_compile;
	long			compiles;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	pthread_mutex_t	cmutex;
}	t_coder;

typedef struct s_hub
{
	int				status;
	int				num_coders;
	long			htime;
	long			tburnout;
	long			tcompile;
	long			tdebug;
	long			trefactor;
	long			tcooldown;
	long			max_compiles;
	char*			scheduler;
	pthread_t		*threads;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	smutex;
	pthread_mutex_t	wmutex;
}	t_hub;

int		setHub(t_hub *hub, char **argv);

int		check_numarg(char *argv);
char	*check_scheduler(char *argv);

#endif