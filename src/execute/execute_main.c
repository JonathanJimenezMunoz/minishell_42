/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:20:43 by david             #+#    #+#             */
/*   Updated: 2024/09/21 20:30:40 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ft_waiter(pid_t *pids, int pipes, t_mini *mini)
{
	int	status;
	int	j;
	int	first;

	first = 1;
	j = -1;
	while (++j < pipes)
	{
		waitpid(pids[j], &status, 0);
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
		redir_exit_capture(mini, status, &first);
	}
	free(pids);
}

static void	child_process(t_mini *mini, t_table *table_aux,
							int prev_fd, int *pipe_fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, 0) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(prev_fd);
	}
	if (table_aux->next)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], 1) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[1]);
	}
	execute_child_process(mini, table_aux);
}

static pid_t	do_fork(t_mini *mini, t_table *table_aux,
					int prev_fd, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		child_process(mini, table_aux, prev_fd, pipe_fd);
	return (pid);
}

static void	ft_forkin(t_mini *mini, t_table *table_aux, int pipes)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	*pids;
	int		i;

	i = -1;
	pids = (pid_t *)malloc(sizeof(pid_t) * pipes);
	if (!pids)
		ft_error(mini, "malloc", "error", 1);
	prev_fd = -1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (table_aux)
	{
		pipe(pipe_fd);
		pids[++i] = do_fork(mini, table_aux, prev_fd, pipe_fd);
		if (prev_fd != -1)
			close(prev_fd);
		close(pipe_fd[1]);
		prev_fd = pipe_fd[0];
		if (!table_aux->next)
			close(pipe_fd[0]);
		table_aux = table_aux->next;
	}
	ft_waiter(pids, pipes, mini);
}

int	execute(t_mini *mini)
{
	t_table	*table_aux;
	int		pipes;

	pipes = 0;
	table_aux = mini->table;
	update_exec_envp_to_envp(mini);
	while (table_aux)
	{
		pipes++;
		table_aux = table_aux->next;
	}
	mini->pipes = pipes;
	table_aux = mini->table;
	if (pipes > 1)
		ft_forkin(mini, table_aux, pipes);
	else if (pipes == 1)
		execute_single_command(mini, table_aux);
	return (0);
}
