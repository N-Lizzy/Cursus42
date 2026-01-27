/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:29:22 by aruiznav          #+#    #+#             */
/*   Updated: 2026/01/14 12:27:55 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthexa_len(unsigned int nbr, char *format)
{
	char	buffer[20];
	int		i;
	int		len;

	i = 0;
	if (nbr == 0)
		return (ft_putchar_len('0'));
	while (nbr)
	{
		buffer[i++] = format[nbr % 16];
		nbr /= 16;
	}
	len = i;
	while (i > 0)
		ft_putchar_len(buffer[--i]);
	return (len);
}
