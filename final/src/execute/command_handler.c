/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:06:32 by david             #+#    #+#             */
/*   Updated: 2024/09/02 15:29:05 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*path_handler(char *param, char **envp)
{
	int		i;
	char	*exec;
	char	**paths;
	char	*temp;

	i = -1;
	paths = ft_split(get_path(envp), ':');
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		exec = ft_strjoin(temp, param);
		free(temp);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_double_array(paths);
			return (exec);
		}
		free(exec);
	}
	free_double_array(paths);
	return (param);
}

static void	execve_handler(char **argv, char **envp)
{
	char	*cmd_path;

	cmd_path = path_handler(argv[0], envp);
	if (execve(cmd_path, argv, envp) == -1)
	{
		if (ft_strchr(cmd_path, '/'))
		{
			if (!access(cmd_path, X_OK | F_OK))
			{
				ft_putstr_fd("bash: ", 2);
				perror(cmd_path);
				exit(126);
			}
			else
			{
				ft_putstr_fd("bash: ", 2);
				ft_putstr_fd(cmd_path, 2);
				exit(127);
			}
		}
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd_path, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}

void	execute_command(t_table *table_aux, t_mini *mini)
{
	int	i;

	i = 0;
	handle_redirection(table_aux);
	i = ft_non_individual_builtins(table_aux, mini);
	if (i == -1)
	{
		if (!table_aux->args && table_aux->in_heredoc)
			exit(mini->exit_status);
		else if (!table_aux->args)
			exit(0);
		else
			execve_handler(table_aux->args, mini->exec_envp);
	}
	else if (i != 0)
		exit(i);
	exit(0);
}
