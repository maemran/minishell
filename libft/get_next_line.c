/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:59:31 by maemran           #+#    #+#             */
/*   Updated: 2025/01/05 03:48:08 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_free(char **s1, char **s2)
{
	free(*s1);
	free(*s2);
	*s2 = NULL;
	return (NULL);
}

static char	*ft_get_line(char **buffer)
{
	char	*pos;
	int		offset;
	char	*line;
	char	*new_buffer;

	pos = ft_strchr(*buffer, '\n');
	if (pos)
		offset = pos - *buffer + 1;
	else
		offset = ft_strlen(*buffer);
	line = malloc(offset + 1);
	if (!line)
		return (NULL);
	line = ft_strncpy(line, *buffer, offset);
	line[offset] = '\0';
	new_buffer = ft_strdup(*buffer + offset);
	if (!new_buffer)
		return (ft_free(&line, &*buffer));
	free(*buffer);
	*buffer = new_buffer;
	return (line);
}

static char	*process(char **buffer, char *result, int fd, int read_value)
{
	char	*temp;

	while (!ft_strchr(*buffer, '\n'))
	{
		read_value = read(fd, result, BUFFER_SIZE);
		if (read_value == -1 || (read_value == 0 && **buffer == '\0'))
			return (ft_free(&result, &*buffer));
		result[read_value] = '\0';
		if (read_value == 0)
			break ;
		temp = ft_strjoin(*buffer, result);
		if (!temp)
			return (ft_free(&result, &*buffer));
		free(*buffer);
		*buffer = temp;
	}
	free(result);
	return (ft_get_line(&*buffer));
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*buffer = NULL;
	int			read_value;

	read_value = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	result = malloc(BUFFER_SIZE + 1);
	if (!result)
		return (NULL);
	if (!buffer)
	{
		buffer = ft_strdup("");
		if (!buffer)
		{
			free(buffer);
			return (NULL);
		}
	}
	return (process(&buffer, result, fd, read_value));
}
