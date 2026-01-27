/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:20:57 by aruiznav          #+#    #+#             */
/*   Updated: 2025/11/25 13:02:16 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nbr)
{
	char		buffer[12];
	long int	nb;
	int			i;
	int			len;

	nb = nbr;
	len = 0;
	i = 0;
	if (nb == 0)
		return (ft_putchar('0'));
	if (nb < 0)
	{
		len += ft_putchar('-');
		nb *= -1;
	}
	while (nb > 0)
	{
		buffer[i++] = (nb % 10) + '0';
		nb /= 10;
	}
	len += i;
	while (i > 0)
		ft_putchar(buffer[--i]);
	return (len);
}
