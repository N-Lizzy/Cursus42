/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 09:50:40 by aruiznav          #+#    #+#             */
/*   Updated: 2025/11/26 12:21:03 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	unsigned int	i;
	char			cc;

	i = 0;
	cc = (char) c;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == cc)
			return ((char *) &str[i]);
		i++;
	}
	if (str[i] == cc)
		return ((char *) &str[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = 0;
	return (str);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}
