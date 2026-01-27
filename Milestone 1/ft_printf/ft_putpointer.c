/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:32:54 by aruiznav          #+#    #+#             */
/*   Updated: 2025/11/19 14:43:08 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hexavalue(unsigned long long nbr, const char *base);

int	ft_putpointer(void *ptr)
{
	long	pointer;
	int		len;

	pointer = (unsigned long long)ptr;
	len = 0;
	if (!ptr)
		return (ft_putstr("(nil)"));
	len += ft_putstr("0x");
	len += hexavalue(pointer, "0123456789abcdef");
	return (len);
}

int	hexavalue(unsigned long long nbr, const char *base)
{
	char	buffer[20];
	int		i;
	int		len;

	i = 0;
	if (nbr == 0)
	{
		ft_putchar(base[0]);
		return (1);
	}
	while (nbr > 0)
	{
		buffer[i++] = base[nbr % 16];
		nbr /= 16;
	}
	len = i;
	while (i > 0)
		ft_putchar(buffer[--i]);
	return (len);
}
