/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:32:45 by david             #+#    #+#             */
/*   Updated: 2023/11/08 00:45:48 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_fd(int fd, char *preview)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 1;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	while (!(ft_strchr2(preview, '\n')) && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if ((!(preview) && bytes_read == 0) || bytes_read == -1)
		{
			free(preview);
			free(buffer);
			return (0);
		}
		buffer[bytes_read] = '\0';
		preview = ft_strjoin2(preview, buffer);
	}
	free(buffer);
	return (preview);
}

char	*ft_get_line(char *preview)
{
	char	*line;
	int		i;

	i = 0;
	while (preview[i] != '\0' && preview[i] != '\n')
		i++;
	if (preview[i] == '\0')
		line = (char *)malloc(sizeof(char) * (i + 1));
	if (preview[i] == '\n')
		line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (0);
	i = -1;
	while (preview[++i] != '\0' && preview[i] != '\n')
		line[i] = preview[i];
	if (preview[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_situation_handler(char *preview)
{
	int		i;
	int		j;
	char	*leftovers;
	int		len_preview;

	i = 0;
	j = 0;
	len_preview = ft_strlen2(preview);
	while (preview[i] != '\0' && preview[i] != '\n')
		i++;
	if (preview[i] == '\0')
	{
		free(preview);
		return (0);
	}
	leftovers = (char *)malloc(sizeof(char) * (len_preview - i + 1));
	i++;
	while (preview[i] != '\0')
		leftovers[j++] = preview[i++];
	leftovers[j] = '\0';
	free(preview);
	return (leftovers);
}

char	*get_next_line(int fd)
{
	static char	*preview;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	preview = ft_read_fd(fd, preview);
	if (!preview)
	{
		free(preview);
		return (0);
	}
	line = ft_get_line(preview);
	preview = ft_situation_handler(preview);
	if (!line || !*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
