/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:20:57 by aruiznav          #+#    #+#             */
/*   Updated: 2026/01/14 12:28:00 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_len(int nbr)
{
	char		buffer[12];
	long int	nb;
	int			i;
	int			len;

	nb = nbr;
	len = 0;
	i = 0;
	if (nb == 0)
		return (ft_putchar_len('0'));
	if (nb < 0)
	{
		len += ft_putchar_len('-');
		nb *= -1;
	}
	while (nb > 0)
	{
		buffer[i++] = (nb % 10) + '0';
		nb /= 10;
	}
	len += i;
	while (i > 0)
		ft_putchar_len(buffer[--i]);
	return (len);
}
