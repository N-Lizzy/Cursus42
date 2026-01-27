/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:19:01 by aruiznav          #+#    #+#             */
/*   Updated: 2025/11/17 15:10:04 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c);
static char	*malloc_word(const char *str, char c);
static void	*ft_free(char **strs, int count);

char	**ft_split(char const *str, char c)
{
	char	**strs;
	int		i;

	i = 0;
	strs = malloc((count_words(str, c) + 1) * sizeof(char *));
	if (!str || !strs)
		return (NULL);
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
		{
			strs[i] = malloc_word(str, c);
			if (!(strs[i]))
				return (ft_free(strs, i));
			i++;
			while (*str && *str != c)
				str++;
		}
	}
	strs[i] = NULL;
	return (strs);
}

static int	count_words(const char *str, char c)
{
	int	cont;
	int	i;

	cont = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			cont++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (cont);
}

static char	*malloc_word(const char *str, char c)
{
	int		len;
	char	*word;
	int		i;

	len = 0;
	i = 0;
	while (str[len] && str[len] != c)
		len++;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	*ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}
