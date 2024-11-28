/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:36:14 by pledieu           #+#    #+#             */
/*   Updated: 2024/11/28 10:46:06 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	clean_buffer(char *buf)
{
	size_t	i;

	i = 0;
	while (buf[i])
		buf[i++] = '\0';
}

static void	shift_buffer(char *buf)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	while (buf[i + j])
	{
		buf[j] = buf[i + j];
		j++;
	}
	buf[j] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX][BUFFER_SIZE + 1];
	char		*res;
	int			bytes_read;

	res = NULL;
	bytes_read = 1;
	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	res = ft_strdup(buffer[fd]);
	if (!res)
		return (NULL);
	while (bytes_read > 0 && ft_check_line(res) == 0)
	{
		bytes_read = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes_read < 0)
			return (clean_buffer(buffer[fd]), free(res), NULL);
		buffer[fd][bytes_read] = '\0';
		res = ft_strjoin(res, buffer[fd]);
		if (!res)
			return (NULL);
	}
	shift_buffer(buffer[fd]);
	if (res[0] == '\0')
		return (free(res), NULL);
	return (res);
}
