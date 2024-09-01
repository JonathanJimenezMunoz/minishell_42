/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 22:00:32 by david             #+#    #+#             */
/*   Updated: 2024/09/01 20:17:11 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	open_input_file(char *file_name, t_mini *mini)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0 || access(file_name, R_OK) < 0)
	{
		ft_putstr_fd("bash: ", 2);
		perror(file_name);
		mini->exit_status = 1;
		mini->error = 1;
	}
	close(fd);
}

void	open_output_file(char *file_name, t_mini *mini, int control)
{
	int	fd;

	if (control == 1)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		perror(file_name);
		mini->exit_status = 1;
		mini->error = 1;
	}
	close(fd);
}
