/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 17:10:48 by aruiznav          #+#    #+#             */
/*   Updated: 2026/09/22 12:08:57 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define ST_IDLE     0
# define ST_COMPILE  1
# define ST_DEBUG    2
# define ST_REFACTOR 3

typedef struct s_dongle
{
	int				is_taken;
	long			last_used;
	pthread_mutex_t	dmutex;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	int				state;
	struct s_hub	*hub;
	long			last_compile;
	long			compiles;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	pthread_mutex_t	cmutex;
}	t_coder;

typedef struct s_request
{
	t_coder		*coder;
	long		order;
	long		deadline;
}	t_request;

typedef struct s_heap
{
	t_request	*data;
	int			size;
	int			capacity;
}	t_heap;

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
	char			*scheduler;
	pthread_t		*threads;
	pthread_t		monitor;
	t_coder			*coders;
	t_dongle		*dongles;
	long			request_order;
	t_heap			heap;
	pthread_mutex_t	smutex;
	pthread_mutex_t	wmutex;
	pthread_cond_t	scond;
}	t_hub;

void		log_state(t_hub *hub, int id, char *msg);

int			set_hub(t_hub *hub, char **argv);
int			set_hub_extra(t_hub *hub);
int			set_arg(t_hub *hub, char **argv);
int			set_dongles(t_hub *hub);
int			set_coders(t_hub *hub);
int			set_coder(t_hub *hub, int i);

int			set_sync(t_hub *hub);
int			set_heap(t_hub *hub);

int			heap_push(t_hub *hub, t_request request);
int			heap_pop(t_hub *hub, t_request *request);

t_request	make_request(t_hub *hub, t_coder *coder);
int			request_compile(t_coder *coder);
int			is_my_turn(t_coder *coder);
int			take_turn(t_coder *coder);
int			take_dongles(t_coder *coder);

int			release_dongles(t_coder *coder);
int			simulation_over(t_hub *hub);
long		get_time(long start_time);

int			check_numarg(char *argv);
char		*check_scheduler(char *argv);
int			request_before(t_hub *hub, t_request *a, t_request *b);
void		swap_request(t_request *a, t_request *b);

void		destroy_dongles(t_hub *hub, int i);
void		destroy_coders(t_hub *hub, int i);

void		*coder_routine(void *arg);
void		*monitor_routine(void *arg);
void		destroy_hub(t_hub *hub);

#endif