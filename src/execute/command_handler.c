/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:06:32 by david             #+#    #+#             */
/*   Updated: 2024/10/20 18:16:10 by dyanez-m         ###   ########.fr       */
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
	if (param[0] == '\0')
		return (param);
	paths = ft_split(get_path(envp), ':');
	while (paths && paths[++i])
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
	char		*cmd_path;
	struct stat	path_stat;

	cmd_path = path_handler(argv[0], envp);
	if (ft_strchr(cmd_path, '/') && stat(cmd_path, &path_stat) == 0
		&& S_ISDIR(path_stat.st_mode))
		ft_dputstr_fd(cmd_path, "Is a directory", 2, 126);
	if (execve(cmd_path, argv, envp) == -1)
	{
		if (ft_strchr(cmd_path, '/'))
		{
			if (!access(cmd_path, X_OK))
				ft_dputstr_fd(cmd_path, strerror(errno), 2, 126);
			else if (!access(cmd_path, F_OK))
				ft_dputstr_fd(cmd_path, strerror(errno), 2, 126);
			else
				ft_dputstr_fd(cmd_path, strerror(errno), 2, 127);
		}
		ft_dputstr_fd(cmd_path, "command not found", 2, 127);
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
		if (!table_aux->args)
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

void	execute_child_process(t_mini *mini, t_table *table_aux)
{
	int	error;

	error = ind_built_with_redir(table_aux, mini);
	if (error == -1)
		execute_command(table_aux, mini);
	else if (error != 0)
		exit(error);
	exit(127);
}

int	execute_single_command(t_mini *mini, t_table *table_aux)
{
	int		error;
	pid_t	pid;
	int		status;

	error = ind_built_with_redir(table_aux, mini);
	if (error == -1)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			execute_command(table_aux, mini);
		}
		else if (pid > 0)
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			waitpid(pid, &status, 0);
			exit_capture(mini, status);
		}
	}
	else if (error != 0)
		mini->exit_status = error;
	return (0);
}
