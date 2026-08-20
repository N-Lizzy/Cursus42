#include "codexion.h"

static void	print_hub(t_hub *hub)
{
	printf("\n╔══════════════════════════════════════════╗\n");
	printf("║     ✅ ARGUMENTOS VÁLIDOS               ║\n");
	printf("╠══════════════════════════════════════════╣\n");
	printf("║  Número de coders     : %d\n", hub->num_coders);
	printf("║  Tiempo a burnout     : %ld ms\n", hub->tburnout);
	printf("║  Tiempo a compilar    : %ld ms\n", hub->tcompile);
	printf("║  Tiempo a debuggear   : %ld ms\n", hub->tdebug);
	printf("║  Tiempo a refactor    : %ld ms\n", hub->trefactor);
	printf("║  Compilaciones req.   : %ld\n", hub->max_compiles);
	printf("║  Cooldown dongle      : %ld ms\n", hub->tcooldown);
	printf("║  Scheduler            : %s\n", hub->scheduler);
	printf("╚══════════════════════════════════════════╝\n");
}

static void	print_error(char **argv)
{
	printf("\n❌ set_hub() detectó argumentos INVÁLIDOS:\n\n");

	if (check_numarg(argv[1]))
		printf("   → [1] coders    : no es un número positivo (\"%s\")\n", argv[1]);
	else if (atoi(argv[1]) > 500 || atoi(argv[1]) < 1)
		printf("   → [1] coders    : fuera de rango 1-500 (\"%s\")\n", argv[1]);

	if (check_numarg(argv[2]))
		printf("   → [2] burnout   : no es un número positivo (\"%s\")\n", argv[2]);
	else if (atoi(argv[2]) < 1)
		printf("   → [2] burnout   : debe ser > 0 (\"%s\")\n", argv[2]);

	if (check_numarg(argv[3]))
		printf("   → [3] compile   : no es un número positivo (\"%s\")\n", argv[3]);
	else if (atoi(argv[3]) < 1)
		printf("   → [3] compile   : debe ser > 0 (\"%s\")\n", argv[3]);

	if (check_numarg(argv[4]))
		printf("   → [4] debug     : no es un número positivo (\"%s\")\n", argv[4]);
	else if (atoi(argv[4]) < 1)
		printf("   → [4] debug     : debe ser > 0 (\"%s\")\n", argv[4]);

	if (check_numarg(argv[5]))
		printf("   → [5] refactor  : no es un número positivo (\"%s\")\n", argv[5]);
	else if (atoi(argv[5]) < 1)
		printf("   → [5] refactor  : debe ser > 0 (\"%s\")\n", argv[5]);

	if (check_numarg(argv[6]))
		printf("   → [6] compiles  : no es un número positivo (\"%s\")\n", argv[6]);
	else if (atoi(argv[6]) < 1)
		printf("   → [6] compiles  : debe ser > 0 (\"%s\")\n", argv[6]);

	if (check_numarg(argv[7]))
		printf("   → [7] cooldown  : no es un número positivo (\"%s\")\n", argv[7]);
	else if (atoi(argv[7]) < 1)
		printf("   → [7] cooldown  : debe ser > 0 (\"%s\")\n", argv[7]);

	if (!check_scheduler(argv[8]))
		printf("   → [8] scheduler : debe ser 'fifo' o 'edf' (\"%s\")\n", argv[8]);

	printf("\nUso: %s <coders> <burnout> <compile> <debug> <refactor> <compiles> <cooldown> <scheduler>\n", argv[0]);
	printf("Ejemplo: %s 5 800 200 200 200 7 300 fifo\n", argv[0]);
}

int	main(int argc, char **argv)
{
	t_hub	hub;

	if (argc != 9)
	{
		printf("\n⚠️  Se esperaban 8 argumentos, se recibieron %d\n", argc - 1);
		printf("Uso: %s <coders> <burnout> <compile> <debug> <refactor> <compiles> <cooldown> <scheduler>\n", argv[0]);
		return (1);
	}

	printf("\n🔍 Probando argumentos:\n");
	printf("   [1] coders    : \"%s\" → %s\n", argv[1], check_numarg(argv[1]) ? "❌ no num" : "✅ num");
	printf("   [2] burnout   : \"%s\" → %s\n", argv[2], check_numarg(argv[2]) ? "❌ no num" : "✅ num");
	printf("   [3] compile   : \"%s\" → %s\n", argv[3], check_numarg(argv[3]) ? "❌ no num" : "✅ num");
	printf("   [4] debug     : \"%s\" → %s\n", argv[4], check_numarg(argv[4]) ? "❌ no num" : "✅ num");
	printf("   [5] refactor  : \"%s\" → %s\n", argv[5], check_numarg(argv[5]) ? "❌ no num" : "✅ num");
	printf("   [6] compiles  : \"%s\" → %s\n", argv[6], check_numarg(argv[6]) ? "❌ no num" : "✅ num");
	printf("   [7] cooldown  : \"%s\" → %s\n", argv[7], check_numarg(argv[7]) ? "❌ no num" : "✅ num");
	printf("   [8] scheduler : \"%s\" → %s\n", argv[8], check_scheduler(argv[8]) ? "✅ ok" : "❌ no válido");

	if (set_hub(&hub, argv))
	{
		print_error(argv);
		return (1);
	}

	print_hub(&hub);
	return (0);
}