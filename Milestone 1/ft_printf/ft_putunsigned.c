/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:32:35 by aruiznav          #+#    #+#             */
/*   Updated: 2025/11/19 12:13:48 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsigned(unsigned int unbr)
{
	char			buffer[20];
	unsigned int	nb;
	int				i;
	int				len;

	nb = unbr;
	len = 0;
	i = 0;
	if (nb == 0)
		return (ft_putchar('0'));
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
