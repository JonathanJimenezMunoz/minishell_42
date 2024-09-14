/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:46 by dyanez-m          #+#    #+#             */
/*   Updated: 2024/09/14 20:37:39 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


static void ft_do_heredoc(t_mini *mini, char *in_heredoc, int fd)
{
	char	*line;
	char	*new_line;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file\
			 (wanted ", 2);
			ft_putstr_fd(in_heredoc, 2);
			mini->exit_status = 1;
			return ;
		}
		if (ft_strncmp(line, in_heredoc, ft_strlen(in_heredoc)) == 0)
		{
			free(line);
			break ;
		}
		new_line = ft_new_line(line, ft_strlen(line), mini);
		free(line);
		ft_putstr_fd(new_line, fd);
		free(new_line);
	}
}

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

static void ft_heredoc_child(t_mini *mini, t_redir *red)
{
	char	*file;
	char    *heredoc;
	int    fd;

	file = heredoc_filename();
	heredoc = ft_strdup(red->file);
	free(red->file);
	red->file = file;
	red->type = TOKEN_UNLINK;
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		ft_dputstr_fd("open", strerror(errno), 2, 1);
	signal(SIGINT, sig_heredoc);
	ft_do_heredoc(mini, heredoc, fd);
	free(heredoc);
	close(fd);
	signal(SIGINT, sig_handler);
}



void ft_check_if_heredoc(t_mini *mini)
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
				ft_heredoc_child(mini, red);
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
