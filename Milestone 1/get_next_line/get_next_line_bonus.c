/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 09:50:42 by aruiznav          #+#    #+#             */
/*   Updated: 2025/12/09 10:39:24 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*next_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = '\0';
	free(buffer);
	return (line);
}

char	*save_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*check_malloc(char *buffer)
{
	buffer = malloc(1 * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	return (buffer);
}

char	*read_file(int fd, char *buffer)
{
	char	*temp;
	int		byte_read;

	if (!buffer)
		buffer = check_malloc(buffer);
	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, temp, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(temp);
			free(buffer);
			return (NULL);
		}
		temp[byte_read] = '\0';
		buffer = join_and_free(buffer, temp);
		if (ft_strchr(temp, '\n'))
			break ;
	}
	free(temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[999];
	char		*line;

	if (fd < 0 || fd >= 999 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = save_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = next_line(buffer[fd]);
	return (line);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int		fd = open("text.txt", O_RDONLY);
// 	char	*A = get_next_line(fd);

// 	while (A)
// 	{
// 		printf("%s", A);
// 		free(A);
// 		A = get_next_line(fd);
// 	}
// }