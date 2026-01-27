/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:43:28 by aruiznav          #+#    #+#             */
/*   Updated: 2025/11/17 10:57:49 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned int	i;
	char			cc;
	char			*result;

	i = 0;
	cc = (char) c;
	result = NULL;
	while (str[i])
	{
		if (str[i] == cc)
			result = (char *) &str[i];
		i++;
	}
	if (str[i] == cc)
		result = (char *) &str[i];
	return (result);
}
