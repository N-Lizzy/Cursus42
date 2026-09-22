#include "codexion.h"

static int	all_compiled(t_hub *hub)
{
	int	i;

	i = 0;
	while (i < hub->num_coders)
	{
		if (hub->coders[i].compiles < hub->max_compiles)
			return (0);
		i++;
	}
	return (1);
}

static int	someone_burned(t_hub *hub, long now)
{
	int	i;

	i = 0;
	while (i < hub->num_coders)
	{
		if (hub->coders[i].compiles >= hub->max_compiles
			|| hub->coders[i].state == ST_COMPILE)
		{
			i++;
			continue ;
		}
		if (now - hub->coders[i].last_compile >= hub->tburnout)
		{
			log_state(hub, hub->coders[i].id, "burned out");
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_hub	*hub;
	long	now;

	hub = (t_hub *)arg;
	while (!hub->status)
	{
		now = get_time(hub->htime);
		if (someone_burned(hub, now) || all_compiled(hub))
		{
			pthread_mutex_lock(&hub->smutex);
			hub->status = 1;
			pthread_cond_broadcast(&hub->scond);
			pthread_mutex_unlock(&hub->smutex);
			break ;
		}
		usleep(200);
	}
	return (NULL);
}