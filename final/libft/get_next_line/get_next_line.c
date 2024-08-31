/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:32:45 by david             #+#    #+#             */
/*   Updated: 2024/08/21 17:12:50 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_return(char **buffer)
{
	free(*buffer);
	*buffer = 0;
	return (0);
}

char	*ft_read_total(int fd, char *buffer)
{
	char	*partial;
	int		bytes;

	partial = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	bytes = 1;
	if (!partial)
		return (free_return(&buffer));
	while (bytes > 0 && !ft_strchr_gnl(buffer, '\n'))
	{
		bytes = read(fd, partial, BUFFER_SIZE);
		if (bytes > 0)
		{
			partial[bytes] = '\0';
			buffer = ft_strjoin2(buffer, partial);
		}
	}
	free(partial);
	if (bytes == -1)
		return (free_return(&buffer));
	return (buffer);
}

char	*ft_get_line(char **buffer)
{
	char	*line;
	char	*without_line;
	char	*new_buffer;
	int		len;

	without_line = ft_strchr_gnl((*buffer), '\n');
	if (!without_line)
		len = ft_strlen_gnl(*buffer);
	else
		len = ft_strlen_gnl(*buffer) - ft_strlen_gnl(without_line) + 1;
	line = ft_substr_gnl(*buffer, 0, len);
	if (!without_line || !line || !(*buffer)[len])
		free_return(buffer);
	else
	{
		new_buffer = ft_substr_gnl(*buffer, len, ft_strlen_gnl(*buffer) - len);
		free_return(buffer);
		*buffer = new_buffer;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer_total;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer_total = ft_read_total(fd, buffer_total);
	if (!buffer_total)
		return (0);
	line = ft_get_line(&buffer_total);
	if (!line)
		free(line);
	return (line);
}
