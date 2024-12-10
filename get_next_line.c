/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:41:13 by achat             #+#    #+#             */
/*   Updated: 2024/12/09 11:20:41 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*jib_line(char **storage)
{
	char	*line;
	char	*newline_ptr;
	char	*temp;

	if (!storage || !*storage)
		return (NULL);
	newline_ptr = ft_strchr(*storage, '\n');
	if (newline_ptr)
	{
		line = ft_substr(*storage, 0, newline_ptr - *storage + 1);
		temp = ft_strdup(newline_ptr + 1);
		free(*storage);
		*storage = temp;
	}
	else
	{
		line = ft_strdup(*storage);
		free(*storage); 
		*storage = NULL;
	}
	return (line);
}

static int	stor_line(int fd, char **storage)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*storage, buffer);
		free(*storage);
		*storage = temp;
		if (ft_strchr (buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read == -1 && *storage)
	{
		free(*storage);
		*storage = NULL;
	}
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = stor_line(fd, &storage);
	if (bytes_read < 0)
	{
		if (storage)
		{
			free(storage);
			storage = NULL;
		}
		return (NULL);
	}
	if (!storage && bytes_read == 0)
		return (NULL);
	line = jib_line(&storage);
	if (!line || !*line)
		return (free(storage), storage = NULL, free(line), line = NULL);
	return (line);
}
// #include <stdio.h>
// #include <fcntl.h>

// int main()
// {
//     int fd;
// 	int i = 0;
//     char *line;

//     fd = open("gg.txt", O_RDONLY);
// 	line = get_next_line(fd);
//     while (i < 2)
// 	{
// 		printf("%s\n", line);
// 		i++;
// 	}
// 	free(line);
//     // line = get_next_line(fd);
// 	close(fd);
// 	return (0);
// }