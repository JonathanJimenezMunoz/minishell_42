/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 00:19:14 by david             #+#    #+#             */
/*   Updated: 2024/08/13 23:25:22 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	write_file(char *file_name, int content)
{
	int		fd;
	char	*number;

	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	number = ft_itoa(content);
	write(fd, number, ft_strlen(number));
	write(fd, "\n", 1);
	free(number);
	close(fd);
}

int	read_file(char *file_name, t_mini *mini)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		mini->error = ft_strdup("00");
		return (-1);
	}
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (-1);
	}
	mini->error = ft_strdup(line);
	free(line);
	close(fd);
	return (0);
}
