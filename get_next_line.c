/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pol <pol@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:47:17 by pledieu           #+#    #+#             */
/*   Updated: 2024/11/24 16:28:59 by pol              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **stash)
{
	char	*line;
	char	*remaining;
	size_t	i;

	i = 0;
	if (!*stash || !**stash)
		return (free(*stash), *stash = NULL, NULL);
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
		i++;
	line = ft_substr(*stash, 0, i);
	if (!line)
		return (free(*stash), *stash = NULL, NULL);
	if ((*stash)[i])
	{
		remaining = ft_substr(*stash, i, ft_strlen(*stash) - i);
		if (!remaining)
			return (free(line), free(*stash), *stash = NULL, NULL);
		free(*stash);
		*stash = remaining;
	}
	else
		return (free(*stash), *stash = NULL, line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(stash), stash = NULL, NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(stash), stash = NULL, NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			stash = ft_strjoin(stash, buffer);
			if (!stash)
				return (free(buffer), NULL);
		}
	}
	free(buffer);
	if (!stash || !*stash)
		return (free(stash), stash = NULL, NULL);
	return (extract_line(&stash));
}
