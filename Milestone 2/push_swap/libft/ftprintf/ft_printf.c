/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:06:16 by aruiznav          #+#    #+#             */
/*   Updated: 2026/01/14 12:35:59 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkformat(char format, va_list args);

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;

	va_start(args, format);
	len = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			len += checkformat(format[i], args);
		}
		else
			len += ft_putchar_len(format[i]);
		i++;
	}
	va_end(args);
	return (len);
}

static int	checkformat(char format, va_list args)
{
	if (format == 'c')
		return (ft_putchar_len(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr_len(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_putpointer_len(va_arg(args, void *)));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr_len(va_arg(args, int)));
	else if (format == 'u')
		return (ft_putunsigned_len(va_arg(args, unsigned int)));
	else if (format == 'x')
		return (ft_puthexa_len((va_arg(args, unsigned int)),
				"0123456789abcdef"));
	else if (format == 'X')
		return (ft_puthexa_len((va_arg(args, unsigned int)),
				"0123456789ABCDEF"));
	else if (format == '%')
		return (ft_putchar_len('%'));
	return (0);
}
