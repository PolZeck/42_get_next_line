/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:36:14 by pledieu           #+#    #+#             */
/*   Updated: 2024/11/25 12:37:13 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <limits.h>

static char	*extract_line(char **stock)
{
	char	*line;
	char	*remaining;
	size_t	i;

	i = 0;
	if (!*stock || !**stock)
		return (free(*stock), *stock = NULL, NULL);
	while ((*stock)[i] && (*stock)[i] != '\n')
		i++;
	if ((*stock)[i] == '\n')
		i++;
	line = ft_substr(*stock, 0, i);
	if (!line)
		return (free(*stock), *stock = NULL, NULL);
	if ((*stock)[i])
	{
		remaining = ft_substr(*stock, i, ft_strlen(*stock) - i);
		if (!remaining)
			return (free(line), free(*stock), *stock = NULL, NULL);
		free(*stock);
		*stock = remaining;
	}
	else
		return (free(*stock), *stock = NULL, line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stock[OPEN_MAX];
	char		*buffer;
	ssize_t		bytes_read;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(stock[fd]), stock[fd] = NULL, NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(stock[fd]), stock[fd] = NULL, NULL);
	bytes_read = 1;
	while (!ft_strchr(stock[fd], '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			stock[fd] = ft_strjoin(stock[fd], buffer);
			if (!stock[fd])
				return (free(buffer), NULL);
		}
	}
	free(buffer);
	if (!stock[fd] || !*stock[fd])
		return (free(stock[fd]), stock[fd] = NULL, NULL);
	return (extract_line(&stock[fd]));
}
