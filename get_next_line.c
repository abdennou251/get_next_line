/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:25:22 by achat             #+#    #+#             */
/*   Updated: 2024/11/25 13:30:59 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char    *line_filler(int fd, char *left_c, char *buffer);
static char    *_set_line(char *line);
static char    *ft_strchr(char *s, int c);

char    *get_next_line(int fd)
{
	static char	*left_c;
	char	*buffer;
	char	*line;
	
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd,buffer, 0) < 0)
	{
		free (buffer);
		if(left_c)
		{
			free(left_c);
			left_c = NULL;
		}
		buffer = NULL;
		return NULL;
	}
	if(!buffer)
		return (NULL);
	line = line_filler(fd, left_c, buffer);
	free(buffer);
	buffer = NULL;
	if(!line)
		return(NULL);
	left_c = _set_line(line);
	return(line);
}

static char *line_filler(int fd,char *left_c, char *buffer)
{
	ssize_t	a_read;
	char	*tmp;
	
	a_read = 1;
	while(a_read > 0)
	{
		a_read = read(fd, buffer, BUFFER_SIZE);
		if (a_read == -1)
		{
			free(left_c);
			left_c = NULL;
			return(NULL);
		}
		else if(a_read == 0)
			break;
		buffer[a_read] = '\0';
		if(!left_c)
			left_c = ft_strdup("");
		tmp = left_c;
		left_c = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if(ft_strchr(buffer, '\n'))
			break;
	}
	return (left_c);
}

static char	*_set_line(char *line_buffer)
{
	char	*left_c;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if(line_buffer[i] == '\0' || line_buffer[1] == '\0')
		return(NULL);
	left_c = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if(*left_c == 0)
	{
		free (left_c);
		left_c = NULL;
	}
	line_buffer[i + 1] = 0;
	return (left_c);
}
static char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}

// #include <stdio.h>
// #include <fcntl.h> // For open()
// #include <unistd.h> // For close()
// #include "get_next_line.h" // Ensure this header has the function prototype

// int main(void)
// {
//     int fd;
//     char *line;

//     // Test 1: Reading from a file
//     printf("===== Test 1: Reading from a file =====\n");
//     fd = open("test_file.txt", O_RDONLY);
//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return (1);
//     }
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line); // Make sure to free the line if your function allocates memory
//     }
//     close(fd);

//     // Test 2: Reading from stdin
//     printf("\n===== Test 2: Reading from stdin =====\n");
//     printf("Type something and press Enter (Ctrl+D to stop):\n");
//     while ((line = get_next_line(STDIN_FILENO)) != NULL)
//     {
//         printf("You entered: %s", line);
//         free(line);
//     }

//     // Test 3: Empty file
//     printf("\n===== Test 3: Empty file =====\n");
//     fd = open("empty_file.txt", O_RDONLY);
//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return (1);
//     }
//     if ((line = get_next_line(fd)) == NULL)
//         printf("No content in file as expected.\n");
//     else
//     {
//         printf("Unexpected content: %s", line);
//         free(line);
//     }
//     close(fd);

//     // Test 4: Large file
//     printf("\n===== Test 4: Large file =====\n");
//     fd = open("large_file.txt", O_RDONLY);
//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return (1);
//     }
//     int line_count = 0;
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("Line %d: %s", ++line_count, line);
//         free(line);
//     }
//     close(fd);

//     // Test 5: Invalid file descriptor
//     printf("\n===== Test 5: Invalid file descriptor =====\n");
//     if ((line = get_next_line(-1)) == NULL)
//         printf("Handled invalid file descriptor correctly.\n");
//     else
//     {
//         printf("Unexpected content: %s", line);
//         free(line);
//     }

//     return 0;
// }
