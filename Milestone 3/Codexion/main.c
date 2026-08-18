/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 17:10:57 by aruiznav          #+#    #+#             */
/*   Updated: 2026/08/18 18:01:12 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	EN ESTE ORDEN:
	number_of_coders -> numero personas
	time_to_burnout -> tiempo antes de morir
	time_to_compile -> tiempo para compilar
	time_to_debug -> tiempo para debuggear
	time_to_refactor -> tiempo para refactorizar
	number_of_compiles_required -> numero de compilaciones TODOS tienen que hacerlas
	dongle_cooldown -> tiempo de cooldown del dongle
	scheduler -> fifo o edf
			fifo -> el dongle se concede por orden de llegada
			edf -> el dongle se concede al que tenga menos tiempo para burnout
				(last_compile_start + time_to_burnout)
*/

int	main(int argc, char **argv)
{
	if (argc != 9)
		return (1);
}


