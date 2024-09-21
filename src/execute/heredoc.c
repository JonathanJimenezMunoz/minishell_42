/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:46 by dyanez-m          #+#    #+#             */
/*   Updated: 2024/09/21 19:41:32 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ft_do_heredoc(t_mini *mini, char *in_heredoc, int fd)
{
	char	*line;
	char	*new_line;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(0);
		if (!line)
			ft_ctrld_error(in_heredoc);
		new_line = ft_new_line(line, ft_strlen(line), mini);
		free(line);
		if (ft_heredoc_cmp(new_line, in_heredoc) == 0)
		{
			free(new_line);
			break ;
		}
		ft_putstr_fd(new_line, fd);
		free(new_line);
	}
}

static void	ft_heredoc_child(t_mini *mini, t_redir *red)
{
	char	*heredoc;
	int		fd;

	signal(SIGINT, sig_heredoc);
	heredoc = ft_strdup(red->file);
	free(red->file);
	fd = open(red->next->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		ft_dputstr_fd("open", strerror(errno), 2, 1);
	ft_do_heredoc(mini, heredoc, fd);
	free(heredoc);
	close(fd);
	exit(0);
}

static void	ft_fork_heredoc(t_mini *mini, t_redir *red)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		ft_dputstr_fd("fork", strerror(errno), 2, 1);
	if (pid == 0)
		ft_heredoc_child(mini, red);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	exit_capture(mini, status);
}

void	ft_check_if_heredoc(t_mini *mini)
{
	t_table	*table;
	t_redir	*red;

	table = mini->table;
	while (table)
	{
		red = table->redir;
		while (red)
		{
			if (red->type == TOKEN_REDIR_DELIMITER)
				ft_fork_heredoc(mini, red);
			if (mini->exit_status == 130)
			{
				mini->error = 1;
				break ;
			}
			red = red->next;
		}
		if (mini->exit_status == 130)
			break ;
		table = table->next;
	}
}
