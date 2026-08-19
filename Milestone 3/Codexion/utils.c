#include "codexion.h"

int	check_numarg(char *argv)
{
	int	i;

	i = 0;

	while(argv[++i])
	{
		if(argv[i] < '0' || argv[i] > '9')
			return (1);
	}

	return atoi(argv);
}

char	*check_scheduler(char *argv)
{
	if ((strcmp(argv, "fifo") == 0) || (strcmp(argv, "edf") == 0))
		return (argv);
	return (NULL);
}
