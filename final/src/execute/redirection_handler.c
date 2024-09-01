/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:18:23 by david             #+#    #+#             */
/*   Updated: 2024/09/01 20:16:02 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_input_redirection(const char *in_redir)
{
	int	fd;

	fd = open(in_redir, O_RDONLY);
	if (fd < 0 || access(in_redir, R_OK) < 0)
	{
		ft_putstr_fd("bash: ", 2);
		perror(in_redir);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	handle_output_redirection(const char *out_redir)
{
	int	fd;

	fd = open(out_redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		perror(out_redir);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	handle_output_append_redirection(const char *out_append)
{
	int	fd;

	fd = open(out_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		perror(out_append);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	handle_redirection(t_table *table_aux)
{
	int	i;

	i = 0;
	while (table_aux->in_redir && table_aux->in_redir[i])
		i++;
	if (i > 0)
		handle_input_redirection(table_aux->in_redir[i - 1]);
	if (table_aux->last_out_redir)
	{
		if (table_aux->append)
			handle_output_append_redirection(table_aux->last_out_redir);
		else
			handle_output_redirection(table_aux->last_out_redir);
	}
}

void	do_redir_handler(t_mini *mini)
{
	t_table	*curr;
	int		i;

	i = -1;
	curr = mini->table;
	if (mini->exit_status == 130)
		return ;
	while (curr)
	{
		while (curr->in_redir && curr->in_redir[++i])
			open_input_file(curr->in_redir[i], mini);
		i = -1;
		while (curr->out_append && curr->out_append[++i])
			open_output_file(curr->out_append[i], mini, 1);
		i = -1;
		while (curr->out_redir && curr->out_redir[++i])
			open_output_file(curr->out_redir[i], mini, 0);
		i = -1;
		curr = curr->next;
	}
}
