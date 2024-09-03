/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:11:02 by david             #+#    #+#             */
/*   Updated: 2024/09/03 19:37:19 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
void	do_heredoc(char *in_heredoc, t_mini *mini, int pipe_fd[2])
{
	char	*line;

	signal(SIGINT, sig_heredoc);
	close(pipe_fd[0]);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			ft_error(mini, "warning: here-document delimited by end-of-file (wanted ", in_heredoc, 0);
			exit(0);
		}
		if (ft_strncmp(line, in_heredoc, ft_strlen(in_heredoc)) == 0)
		{
			free(line);
			close(pipe_fd[1]);
			break ;
		}
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}

static void	here_doc_father(int pipe_fd[2], pid_t pid, t_mini *mini)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("Dup2 error: initialize");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	waitpid(pid, &status, 0);
	exit_capture(mini, status);
}

void	here_doc_case(t_mini *mini, t_table *table_aux, int i)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe error: initialize");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork error: initialize");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		do_heredoc(table_aux->in_heredoc[i], mini, pipe_fd);
	else
		here_doc_father(pipe_fd, pid, mini);
}

void	handle_heredoc_child(t_table *table, t_mini *mini, int i, int *p10, int pipe_fd[2])
{
	if (i != 0)
	{
		if (dup2(*p10, 0) == -1)
			ft_dputstr_fd("dup2", strerror(errno), 2, 1);
		close(*p10);
	}
	if (table->in_heredoc[i + 1])
	{
		if (dup2(pipe_fd[1], 1) == -1)
			ft_dputstr_fd("dup2", strerror(errno), 2, 1);
		close(pipe_fd[1]);
	}
	if (!table->in_heredoc[i + 1])
		handle_redirection(table);
	here_doc_case(mini, table, i);
}

void	handle_heredoc_parent(t_table *table, t_mini *mini, int i, int *p10, int pid, int pipe_fd[2])
{
	int		status;

	if (table->in_heredoc[i + 1])
	{
		close(pipe_fd[1]);
		*p10 = pipe_fd[0];
	}
	else
	{
		if (pipe_fd[0] != -1)
			close(pipe_fd[0]);
	}
	waitpid(pid, &status, 0);
	exit_capture(mini, status);
}
*/


/*Si todo esto funciona debria meter todo lso ints en una estrucutura*/
/*
void	ft_prepare_heredoc(t_mini *mini, t_table *table)
{
	int	i;
	int	pipe_fd[2];
	int	pid;
	int	p10;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	i = 0;
	if (mini->exit_status == 130)
		return ;
	while (table->in_heredoc[i])
	{
		if (table->in_heredoc[i + 1])
		{
			if (pipe(pipe_fd) == -1)
				ft_dputstr_fd("pipe", strerror(errno), 2, 1);
		}
		pid = fork();
		if (pid == 0)
			handle_heredoc_child(table, mini, i, &p10, pipe_fd);
		else if (pid > 0)
			handle_heredoc_parent(table, mini, i, &p10, pid, pipe_fd);
		else
			ft_dputstr_fd("fork", strerror(errno), 2, 1);
		i++;
	}
}

void	ft_check_if_heredoc(t_mini *mini)
{
	t_table *table;

	table = mini->table;
	while (table)
	{
		if (table->in_heredoc)
		{
			ft_prepare_heredoc(mini, table);
			if (mini->exit_status == 130)
			{
				mini->error = 0;
				break ;
			}
		}
		table = table->next;
	}
}*/