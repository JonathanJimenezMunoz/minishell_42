/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:14:23 by dyanez-m          #+#    #+#             */
/*   Updated: 2024/10/15 16:41:07 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	restore_fds(int og_in, int og_out)
{
	if (dup2(og_in, STDIN_FILENO) < 0)
	{
		perror("Error restoring stdin");
		exit(EXIT_FAILURE);
	}
	close(og_in);
	if (dup2(og_out, STDOUT_FILENO) < 0)
	{
		perror("Error restoring stdout");
		exit(EXIT_FAILURE);
	}
	close(og_out);
}

static void	handle_input_redirection_export(char *in_redir, t_mini *mini,
	int og_in, int og_out)
{
	int	fd;

	fd = open(in_redir, O_RDONLY);
	if (fd < 0 || access(in_redir, R_OK) < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(in_redir, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		mini->exit_status = 1;
		restore_fds(og_in, og_out);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		mini->exit_status = 1;
		restore_fds(og_in, og_out);
	}
	close(fd);
}

static void	handle_output_redirection_export(char *out_redir, t_mini *mini,
	int og_in, int og_out)
{
	int	fd;

	fd = open(out_redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(out_redir, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		mini->exit_status = 1;
		restore_fds(og_in, og_out);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		mini->exit_status = 1;
		restore_fds(og_in, og_out);
	}
	close(fd);
}

static void	handle_output_append_redirection_export(char *out_append,
	t_mini *mini, int og_in, int og_out)
{
	int	fd;

	fd = open(out_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(out_append, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		mini->exit_status = 1;
		restore_fds(og_in, og_out);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		mini->exit_status = 1;
		restore_fds(og_in, og_out);
	}
	close(fd);
}

void	handle_redirection_export(t_envp *envp, t_table *table_aux,
	t_mini *mini)
{
	int		og_in;
	int		og_out;
	t_redir	*red;

	og_in = dup(STDIN_FILENO);
	og_out = dup(STDOUT_FILENO);
	red = table_aux->redir;
	while (red)
	{
		if (red->type == TOKEN_REDIR_IN || red->type == TOKEN_UNLINK)
			handle_input_redirection_export(red->file, mini, og_in, og_out);
		else if (red->type == TOKEN_REDIR_OUT)
			handle_output_redirection_export(red->file, mini, og_in, og_out);
		else if (red->type == TOKEN_REDIR_APPEND)
			handle_output_append_redirection_export(red->file, mini,
				og_in, og_out);
		red = red->next;
	}
	print_envp_declare(envp);
	restore_fds(og_in, og_out);
}
