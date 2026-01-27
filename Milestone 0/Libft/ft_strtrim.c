/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:23:05 by aruiznav          #+#    #+#             */
/*   Updated: 2025/11/17 10:57:52 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(const char *set, char c);
static char	*new_str(const char *s1, size_t start, size_t end);

char	*ft_strtrim(const char *str, const char *set)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str) - 1;
	if (ft_strlen(str) == 0)
		return (ft_strdup(""));
	while (check_set(set, str[i]))
		i++;
	while (check_set(set, str[j]))
		j--;
	return (new_str(str, i, j - (i - 1)));
}

static char	*new_str(const char *s1, size_t start, size_t len)
{
	char	*str;
	size_t	i;

	if (len <= 0 || start >= ft_strlen(s1))
		return (ft_strdup(""));
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s1[start + i];
		i++;
	}
	return (str);
}

static int	check_set(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
