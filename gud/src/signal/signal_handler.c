/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:05:04 by david             #+#    #+#             */
/*   Updated: 2024/09/01 18:16:52 by david            ###   ########.fr       */
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

void	exit_capture(t_mini *mini, int status)
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
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			mini->exit_status = 131;
		}
		else if (WTERMSIG(status) == SIGINT)
		{
			ft_putstr_fd("\n", 2);
			mini->exit_status = 130;
		}
		else
		{
			mini->exit_status = 1;
		}
	}
}

void	redir_exit_capture(t_mini *mini, int status, int *first)
{
	if (WIFEXITED(status))
		mini->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && *first == 1)
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 2);
			mini->exit_status = 131;
		}
		else if (WTERMSIG(status) == SIGINT)
		{
			ft_putstr_fd("\n", 2);
			mini->exit_status = 130;
		}
		*first = 0;
	}
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sigint = 1;
	}
}
void	while_signals(t_mini *mini)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	if (g_sigint == 1)
	{
		mini->exit_status = 130;
		g_sigint = 0;
	}
}
