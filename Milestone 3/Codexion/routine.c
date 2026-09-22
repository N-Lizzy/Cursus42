#include "codexion.h"

void	*coder_routine(void *arg)
{
	t_coder	*coder;
	t_hub	*hub;

	coder = (t_coder *)arg;
	hub = coder->hub;
	while (!hub->status && coder->compiles < hub->max_compiles)
	{
		if (request_compile(coder) || take_turn(coder))
	        break ;
		coder->state = ST_COMPILE;
		coder->last_compile = get_time(hub->htime);
		log_state(hub, coder->id, "is compiling");
		usleep(hub->tcompile * 1000);
		release_dongles(coder);
		coder->compiles++;
		coder->state = ST_DEBUG;
		log_state(hub, coder->id, "is debugging");
		usleep(hub->tdebug * 1000);
		coder->state = ST_REFACTOR;
		log_state(hub, coder->id, "is refactoring");
		usleep(hub->trefactor * 1000);
	}
	return (NULL);
}