/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:29:22 by aruiznav          #+#    #+#             */
/*   Updated: 2025/11/19 15:09:41 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexa(unsigned int nbr, char *format)
{
	char	buffer[20];
	int		i;
	int		len;

	i = 0;
	if (nbr == 0)
		return (ft_putchar('0'));
	while (nbr)
	{
		buffer[i++] = format[nbr % 16];
		nbr /= 16;
	}
	len = i;
	while (i > 0)
		ft_putchar(buffer[--i]);
	return (len);
}
