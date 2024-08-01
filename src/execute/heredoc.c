/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:11:02 by david             #+#    #+#             */
/*   Updated: 2024/08/01 17:44:45 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	here_doc_terminal(t_table *table, int pipe_fd[2])
{
	char	*line;

	close(pipe_fd[0]);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(0);
		if (ft_strncmp(line, table->in_heredoc, strlen(table->in_heredoc)) == 0)
		{
			free(line);
			close(pipe_fd[1]);
			exit(0);
		}
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}

static void	here_doc_father(int pipe_fd[2], pid_t pid)
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("Dup2 error: initialize");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	waitpid(pid, NULL, 0);
}

void	here_doc_case(t_table *table_aux)
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
		here_doc_terminal(table_aux, pipe_fd);
	else
		here_doc_father(pipe_fd, pid);
}
