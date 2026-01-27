/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:32:54 by aruiznav          #+#    #+#             */
/*   Updated: 2026/01/14 12:28:02 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putpointer_len(void *ptr)
{
	long	pointer;
	int		len;

	pointer = (unsigned long long)ptr;
	len = 0;
	if (!ptr)
		return (ft_putstr_len("(nil)"));
	len += ft_putstr_len("0x");
	len += ft_puthexa_len(pointer, "0123456789abcdef");
	return (len);
}
