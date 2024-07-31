/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:48:47 by david             #+#    #+#             */
/*   Updated: 2024/07/31 18:39:44 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	handle_child_process(char **envp_lst, 
	t_table *table_aux, int in_fd, int pipe_fd[2])
{
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(in_fd);
	}
	if (table_aux->next)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[1]);
	}
	close(pipe_fd[0]);
	handle_redirection(table_aux);
	if (table_aux->in_heredoc)
		here_doc_case(table_aux);
	execute_command(table_aux, envp_lst);
	exit(0);
}

static void	handle_parent_process(pid_t pid, int pipe_fd[2], int *in_fd)
{
	waitpid(pid, NULL, 0);
	close(pipe_fd[1]);
	*in_fd = pipe_fd[0];
}

static void	create_pipe(t_mini *mini, int pipe_fd[2], t_table *table_aux)
{
	if (table_aux->next)
	{
		if (pipe(pipe_fd) == -1)
			ft_error(mini, "pipe", "error");
	}
}

static void	close_pipes(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int execute(t_mini *mini, char **envp)
{
	t_table	*table_aux;
	pid_t	pid;
	int		in_fd;
	int		pipe_fd[2];

	in_fd = STDIN_FILENO;
	table_aux = mini->table;
	while (table_aux)
	{
		close_pipes(pipe_fd);
		create_pipe(mini, pipe_fd, table_aux);
		pid = fork();
		if (pid == 0)
			handle_child_process(envp, table_aux, in_fd, pipe_fd);
		else if (pid > 0)
			handle_parent_process(pid, pipe_fd, &in_fd);
		else
			ft_error(mini, "fork", "error");
		table_aux = table_aux->next;
	}
	return (0);
}
