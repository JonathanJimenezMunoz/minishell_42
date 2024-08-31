/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:11:02 by david             #+#    #+#             */
/*   Updated: 2024/08/31 18:16:26 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	here_doc_terminal(int pipe_fd[2], t_table *table_aux)
{
	char	*line;
	int		i;

	i = -1;
	signal(SIGINT, sig_heredoc);
	close(pipe_fd[0]);
	while (table_aux && table_aux->in_heredoc[++i])
	{
		while (1)
		{
			write(STDOUT_FILENO, "> ", 2);
			line = get_next_line(0);
			if (ft_strncmp(line, table_aux->in_heredoc[i],
					ft_strlen(table_aux->in_heredoc[i])) == 0)
			{
				free(line);
				close(pipe_fd[1]);
				break ;
			}
			ft_putstr_fd(line, pipe_fd[1]);
			free(line);
		}
	}
	close(pipe_fd[1]);
}

static void	here_doc_father(int pipe_fd[2], pid_t pid, t_mini *mini)
{
	int	status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("Dup2 error: initialize");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	waitpid(pid, &status, 0);
	exit_capture_heredoc(mini, status);
}

void	here_doc_case(t_table *table_aux, t_mini *mini)
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
		here_doc_terminal(pipe_fd, table_aux);
	else
		here_doc_father(pipe_fd, pid, mini);
}

void	process_heredoc(t_mini *mini)
{
	t_table	*current;

	current = mini->table;
	while (current)
	{
		if (current->in_heredoc)
			here_doc_case(current, mini);
		if (mini->exit_status == 130)
		{
			//FALG REDIRECTIONS = 0 //AKA NO HACER EL EXECUTE
			mini->error = 1;
			break ;
		}
		current = current->next;
	}
}
