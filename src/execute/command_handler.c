/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:06:32 by david             #+#    #+#             */
/*   Updated: 2024/08/02 00:55:36 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ft_free_path(char **string)
{
	int	i;

	i = -1;
	while (string[++i])
		free(string[i]);
	free(string);
}

static char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	return (envp[i] + 5);
}

static char	*path_handler(char *param, char **envp)
{
	int		i;
	char	*exec;
	char	**paths;

	i = -1;
	paths = ft_split(get_path(envp), ':');
	while (paths[++i])
	{
		exec = ft_strjoin(ft_strjoin(paths[i], "/"), param);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free(param);
			return (exec);
		}
		free(exec);
	}
	ft_free_path(paths);
	return (param);
}

static void error_handler(char *cmd_path, char **argv)
{
	if (ft_strchr(cmd_path, '/') == NULL)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		write_file(".err", 127);
		exit(127);
	}
}

void execute_command(t_table *table_aux, char **envp)
{
	char	**argv;
	char	*cmd_path;
	char	*total_arg;
	char 	*cmd;

	cmd = ft_strjoin(table_aux->cmd, " ");
	if (table_aux->args)
		total_arg = ft_strjoin2(cmd, table_aux->args);
	else
		total_arg = cmd;
	argv = ft_split(total_arg, ' ');
	free(total_arg);
	if (argv[0] == NULL)
		exit(0);
	cmd_path = path_handler(argv[0], envp);
	error_handler(cmd_path, argv);
	write_file(".err", 0);
	execve(cmd_path, argv, envp);
	perror(argv[0]);
	exit(127);
}
