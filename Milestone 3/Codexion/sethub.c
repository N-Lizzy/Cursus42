#include "codexion.h"

int	setHub(t_hub *hub, char **argv)
{
	hub->num_coders = check_numarg(argv[1]);
	hub->tburnout = check_numarg(argv[2]);
	hub->tcompile = check_numarg(argv[3]);
	hub->tdebug = check_numarg(argv[4]);
	hub->trefactor = check_numarg(argv[5]);
	hub->max_compiles = check_numarg(argv[6]);
	hub->tcooldown = check_numarg(argv[7]);
	hub->scheduler = check_scheduler(argv[8]);

	if (hub->num_coders > 500 || !hub->num_coders || !hub-> tburnout
		|| !hub-> tcompile || !hub->tdebug || !hub->trefactor || !hub->max_compiles
		|| !hub->tcooldown || !hub->scheduler)
		return (1);

	hub->status = 0;
	return (0);
}
