/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:11:02 by david             #+#    #+#             */
/*   Updated: 2024/09/01 16:28:04 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void here_doc_terminal(int pipe_fd[2], char *in_heredoc, t_mini *mini)
{
	char	*line;
	char	*new_line;

	ft_putendl_fd(in_heredoc, 2);
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
			break ;
		}
		new_line = ft_new_line(line, ft_strlen(line), mini);
		free(line);
		ft_putstr_fd(new_line, pipe_fd[1]);
		free(new_line);
	}
	close(pipe_fd[1]);
}

static void here_doc_child(t_table *table_aux, t_mini *mini, int pipe_fd[2])
{
	int		i;

	i = 0;
	signal(SIGINT, sig_heredoc);
	while (table_aux->in_heredoc && table_aux->in_heredoc[i])
	{
		here_doc_terminal(pipe_fd, table_aux->in_heredoc[i], mini);
		i++;
	}
}

static void here_doc_dad(t_mini *mini, pid_t pid, int pipe_fd[2])
{
	int		status;

	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	exit_capture(mini, status);
}

void	here_doc_case(t_table *table_aux, t_mini *mini)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork error: initialize");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		here_doc_child(table_aux, mini, pipe_fd);
	else
		here_doc_dad(mini, pid, pipe_fd);
}

static pid_t here_doc_case_fork(t_table *current, t_mini *mini, int pipe_fd[2], int prev_fd, int i, int len)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork error: initialize");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (prev_fd != -1)
		{
			if (dup2(prev_fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			close(prev_fd);
		}
		if (i != len - 1)
		{
			close(pipe_fd[0]);
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			close(pipe_fd[1]);
		}
		if (current->last_out_redir)
		{
			if (current->out_append)
				handle_output_append_redirection(current->last_out_redir);
			else
				handle_output_redirection(current->last_out_redir);
		}
		here_doc_case(current, mini);
	}
	return (pid);
}
void	process_heredoc(t_mini *mini)
{
	t_table	*current;
	int	i;
	int	pipe_fd[2];
	int prev_fd;
	pid_t	*pids;
	int	len;
	len = 0;
	current = mini->table;
	while (current)
	{
		if (current->in_heredoc)
			len++;
		current = current->next;
	}
	current = mini->table;
	pids = malloc(sizeof(pid_t) * len);
	prev_fd = -1;
	i = 0;
	while (current)
	{
		if (current->in_heredoc)
		{
			printf("here_doc_case_fork\n");
			pipe(pipe_fd);
			pids[i] = here_doc_case_fork(current, mini, pipe_fd, prev_fd, i, len);
			if (prev_fd != -1)
				close(prev_fd);
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
			if (i == len - 1)
				close(pipe_fd[0]);
			i++;
		}
		if (mini->exit_status == 130)
		{
			//FALG REDIRECTIONS = 0 //AKA NO HACER EL EXECUTE
			mini->error = 1;
			break ;
		}
		current = current->next;
	}
	free(pids);
}