/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiznav <aruiznav@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 09:50:42 by aruiznav          #+#    #+#             */
/*   Updated: 2025/12/09 10:31:08 by aruiznav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_file(int fd, char *buffer);
static char	*check_malloc(char *buffer);
static char	*save_line(char *buffer);
static char	*next_line(char *buffer);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = save_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = next_line(buffer);
	return (line);
}

static char	*read_file(int fd, char *buffer)
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

static char	*check_malloc(char *buffer)
{
	buffer = malloc(1 * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	return (buffer);
}

static char	*save_line(char *buffer)
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

static char	*next_line(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
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