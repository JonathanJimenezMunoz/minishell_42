/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:46 by dyanez-m          #+#    #+#             */
/*   Updated: 2024/09/14 17:50:26 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
static void ft_heredoc_child(t_mini *mini, t_table *table)
{
	char	*line;
	char	*new_line;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(0);
		if (!line)
			ft_dputstr_fd(in_heredoc, "warning: here-document delimited by end-of-file (wanted ", 2, 1);

		if (ft_strncmp(line, in_heredoc, ft_strlen(in_heredoc)) == 0)
		{
			free(line);
			break ;
		}
		new_line = ft_new_line(line, ft_strlen(line), mini);
		free(line);
		ft_putstr_fd(new_line, pipe_fd[1]);
		free(new_line);
	}
	close(pipe_fd[1]);
}*/
/*
static char *heredoc_filename(void)
{
	static int i;
	char *num;
	char *file;

	num = ft_itoa(i++);
	file = ft_strjoin(".heredoc_", num);
	free(num);
	return (file);
}
static void ft_heredoc_child(t_mini *mini, t_table *table)
{
	char	*file;


}
static void ft_heredoc(t_mini *mini, t_table *table)
{
	pid_t	pid;
	int		status;
	int		i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		while (table->in_heredoc[i])
			ft_heredoc_child(mini, table);
	}
	else if (pid < 0)
		ft_dputstr_fd("fork", strerror(errno), 2, 1);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	exit_capture(mini, status);
}

void ft_check_if_heredoc(t_mini *mini)
{
	t_table *table;

	table = mini->table;
	while (table)
	{
		if (table->in_heredoc)
			ft_heredoc(mini, table);
		if (mini->exit_status == 130)
		{
			mini->error = 0;
			break ;
		}
		table = table->next;
	}
}*/
