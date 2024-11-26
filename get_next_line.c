/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:47:17 by pledieu           #+#    #+#             */
/*   Updated: 2024/11/26 15:47:52 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	reset_buffer(char *buf)
{
	size_t	idx;

	idx = 0;
	while (buf[idx])
		buf[idx++] = '\0';
}

static void	shift_buffer(char *buf)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
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
	static char	mem[BUFFER_SIZE + 1] = "\0";
	char		*res;
	int			bytes_read;

	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	res = ft_strdup(mem);
	if (!res)
		return (NULL);
	while (bytes_read && ft_check_line(res) == 0)
	{
		bytes_read = read(fd, mem, BUFFER_SIZE);
		if (bytes_read < 0)
			return (reset_buffer(mem), free(res), NULL);
		mem[bytes_read] = '\0';
		res = ft_strjoin(res, mem);
		if (!res)
			return (NULL);
	}
	shift_buffer(mem);
	if (res[0] == 0)
		return (free(res), NULL);
	return (res);
}
