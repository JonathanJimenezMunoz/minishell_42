/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:18:23 by david             #+#    #+#             */
/*   Updated: 2024/09/14 19:34:21 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_input_redirection(char *in_redir)
{
	int	fd;

	fd = open(in_redir, O_RDONLY);
	if (fd < 0 || access(in_redir, R_OK) < 0)
		ft_dputstr_fd(in_redir, strerror(errno), 2, EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	handle_output_redirection(char *out_redir)
{
	int	fd;

	fd = open(out_redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_dputstr_fd(out_redir, strerror(errno), 2, EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	handle_output_append_redirection(char *out_append)
{
	int	fd;

	fd = open(out_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		ft_dputstr_fd(out_append, strerror(errno), 2, EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	handle_redirection(t_table *table_aux)
{
	t_redir	*red;

	red = table_aux->redir;
	while (red)
	{
		if (red->type == TOKEN_REDIR_IN || red->type == TOKEN_UNLINK)
			handle_input_redirection(red->file);
		else if (red->type == TOKEN_REDIR_OUT)
			handle_output_redirection(red->file);
		else if (red->type == TOKEN_REDIR_APPEND)
			handle_output_append_redirection(red->file);
		red = red->next;
	}
}
