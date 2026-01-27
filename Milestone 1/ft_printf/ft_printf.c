/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:06:16 by aruiznav          #+#    #+#             */
/*   Updated: 2026/01/15 12:37:43 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
			len += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (len);
}

static int	checkformat(char format, va_list args)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_putpointer(va_arg(args, void *)));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (format == 'u')
		return (ft_putunsigned(va_arg(args, unsigned int)));
	else if (format == 'x')
		return (ft_puthexa((va_arg(args, unsigned int)), "0123456789abcdef"));
	else if (format == 'X')
		return (ft_puthexa((va_arg(args, unsigned int)), "0123456789ABCDEF"));
	else if (format == '%')
		return (ft_putchar('%'));
	return (0);
}

int main(void)
{
	ft_printf("\n");
}