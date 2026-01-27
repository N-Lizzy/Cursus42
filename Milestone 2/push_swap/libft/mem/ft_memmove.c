/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:55:19 by aruiznav          #+#    #+#             */
/*   Updated: 2025/11/17 10:56:58 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	const char	*temp_src;
	char		*temp_dest;
	size_t		i;

	i = 0;
	if (!src && !dest)
		return (NULL);
	temp_dest = (char *) dest;
	temp_src = (const char *) src;
	if (temp_dest > temp_src)
	{
		while (len-- > 0)
			temp_dest[len] = temp_src[len];
	}
	else
	{
		while (i < len)
		{
			temp_dest[i] = temp_src[i];
			i++;
		}
	}
	return (dest);
}
