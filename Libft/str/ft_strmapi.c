/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:18:40 by aruiznav          #+#    #+#             */
/*   Updated: 2025/11/17 10:57:40 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	char				*temp;
	unsigned int		len;
	unsigned int		i;

	temp = malloc(ft_strlen(str) + 1);
	len = ft_strlen(str);
	i = 0;
	if (!temp)
		return (NULL);
	while (i < len)
	{
		temp[i] = (*f)(i, str[i]);
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
