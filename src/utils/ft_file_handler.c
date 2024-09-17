/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:45:43 by dyanez-m          #+#    #+#             */
/*   Updated: 2024/09/14 15:36:18 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	open_input_file(char *file_name, t_mini *mini)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0 || access(file_name, R_OK) < 0)
	{
		mini->exit_status = 1;
		mini->flag_redir = 1;
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
		mini->exit_status = 1;
		mini->flag_redir = 1;
	}
	close(fd);
}
