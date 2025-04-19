/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:09:40 by salshaha          #+#    #+#             */
/*   Updated: 2025/04/14 09:54:31 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2, int *coll)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(result, s1, len1);
	free(s1);
	ft_memcpy(result + len1, s2, len2 + 1);
	if (len1 + len2 > 0 && *(result + len1 + len2 - 1) == '\n')
		*coll = 0;
	return (result);
}

char	*init_line(char *remin, int *loca)
{
	size_t	len;
	char	*line;

	len = 0;
	while (remin[len] && remin[len] != '\n')
		len++;
	len++;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, remin, len);
	line[len] = '\0';
	if (len > 0 && line[len - 1] == '\n')
		*loca = len - 1;
	return (line);
}

size_t	get_line(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (-1);
	while (i < BUFFER_SIZE)
	{
		if (line[i] == '\n' || line[i] == '\0')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*extract_line(char *line, char *remin, int *loca, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	read_check;
	size_t	line_size;

	while (*loca == -1)
	{
		ft_bzero(buffer, (BUFFER_SIZE + 1));
		read_check = read(fd, buffer, BUFFER_SIZE);
		if (read_check == -1)
		{
			free(line);
			ft_bzero(remin, (BUFFER_SIZE + 1));
			return (NULL);
		}
		line_size = get_line(buffer);
		ft_strlcpy_gnl(remin, &buffer[line_size], (BUFFER_SIZE + 1));
		buffer[line_size] = '\0';
		line = ft_strjoin_gnl(line, buffer, loca);
		if (read_check == 0)
		{
			ft_bzero(remin, BUFFER_SIZE + 1);
			break ;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	remin[BUFFER_SIZE + 1];
	char		*line;
	int			loca;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	loca = -1;
	line = init_line(remin, &loca);
	if (!line)
		return (NULL);
	ft_strlcpy_gnl(remin, &remin[loca + 1], BUFFER_SIZE + 1);
	line = extract_line(line, remin, &loca, fd);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
