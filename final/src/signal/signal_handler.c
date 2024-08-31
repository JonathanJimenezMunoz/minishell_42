/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:05:04 by david             #+#    #+#             */
/*   Updated: 2024/08/31 18:32:16 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putendl_fd("", 1);
		exit(130);
	}
}

void	exit_capture_heredoc(t_mini *mini, int status)
{
	if (WIFEXITED(status))
	{
		if (status == 256)
			mini->exit_status = 1;
		else
			mini->exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			ft_putstr_fd("\n", 2);
			mini->exit_status = 130;
		}
	}
}