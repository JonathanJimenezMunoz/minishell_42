/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:48:47 by david             #+#    #+#             */
/*   Updated: 2024/08/13 23:47:48 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	handle_child_process(char **envp_lst,
	t_table *table_aux, t_mini *mini)
{
	if (mini->i != 0)
	{
		if (dup2(mini->p10, 0) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(mini->p10);
	}
	if (table_aux->next)
	{
		if (dup2(mini->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(mini->pipe_fd[1]);
	}
	handle_redirection(table_aux);
	if (table_aux->in_heredoc)
		here_doc_case(table_aux);
	if (is_builtin_tech(table_aux) == 0)
		execute_command(table_aux, envp_lst);
}

static void	handle_parent_process(t_mini *mini, t_table *table_aux)
{
	if (table_aux->next)
	{
		close(mini->pipe_fd[1]);
		mini->p10 = mini->pipe_fd[0];
	}
	else
	{
		if (mini->pipe_fd[0] != -1)
			close(mini->pipe_fd[0]);
	}
	waitpid(mini->pid, NULL, 0);
}

static void	create_pipe(int pipe_fd[2], t_table *table_aux)
{
	if (table_aux->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

static void	execute_aux(t_mini *mini, char **envp, t_table *table_aux)
{
	create_pipe(mini->pipe_fd, table_aux);
	mini->pid = fork();
	if (mini->pid == 0)
		handle_child_process(envp, table_aux, mini);
	else if (mini->pid > 0)
		handle_parent_process(mini, table_aux);
	else
		ft_error(mini, "fork", "error");
}

int	execute(t_mini *mini, char **envp)
{
	t_table	*table_aux;
	int		it_was;

	it_was = 1;
	table_aux = mini->table;
	mini->i = 0;
	if (table_aux && table_aux->next == NULL && is_builtin(table_aux) == 0)
		it_was = ft_built(table_aux, mini);
	while (table_aux && it_was)
	{
		while (table_aux && is_builtin_tech(table_aux) == 1 && table_aux->next)
			table_aux = table_aux->next;
		if (is_builtin_tech(table_aux) == 0)
			execute_aux(mini, envp, table_aux);
		table_aux = table_aux->next;
		mini->i++;
	}
	return (0);
}
