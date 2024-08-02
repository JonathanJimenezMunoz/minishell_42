/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:18:23 by david             #+#    #+#             */
/*   Updated: 2024/08/02 01:00:36 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	handle_input_redirection(const char *in_redir)
{
	int	fd;

	fd = open(in_redir, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		perror(in_redir);
		write_file(".err", 1);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

static void	handle_output_redirection(const char *out_redir)
{
	int	fd;

	fd = open(out_redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		perror(out_redir);
		write_file(".err", 1);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

static void	handle_output_append_redirection(const char *out_append)
{
	int	fd;

	fd = open(out_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		perror(out_append);
		write_file(".err", 1);
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
	if (table_aux->in_redir)
		handle_input_redirection(table_aux->in_redir);
	if (table_aux->out_redir)
		handle_output_redirection(table_aux->out_redir);
	if (table_aux->out_append)
		handle_output_append_redirection(table_aux->out_append);
}
