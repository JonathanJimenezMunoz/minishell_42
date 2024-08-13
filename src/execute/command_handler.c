/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:06:32 by david             #+#    #+#             */
/*   Updated: 2024/08/13 23:07:12 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
			return (exec);
		free(exec);
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (param);
}

/*void execute_command(t_table *table_aux, char **envp)
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
	printf("argv[0]: %s\n", argv[0]);
	execve(cmd_path, argv, envp);
	perror(argv[0]);
	exit(127);
}*/

static void	execve_handler(char **argv, char **envp)
{
	char	*cmd_path;

	cmd_path = path_handler(argv[0], envp);
	if (ft_strchr(cmd_path, '/') == NULL)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		write_file(".err", 127);
		if (access(cmd_path, F_OK | X_OK) == 0)
			free(cmd_path);
		free_argv(argv);
		exit(127);
	}
	write_file(".err", 0);
	execve(cmd_path, argv, envp);
	if (access(cmd_path, F_OK | X_OK) == 0)
		free(cmd_path);
	free_argv(argv);
	perror(argv[0]);
	exit(127);
}

static int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args && args[count] != NULL)
		count++;
	return (count);
}

static char	**duplicate_args(char *cmd, char **args, int args_count)
{
	char	**argv;
	int		i;

	i = 0;
	argv = (char **)malloc((args_count + 2) * sizeof(char *));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(cmd);
	while (i < args_count)
	{
		argv[i + 1] = ft_strdup(args[i]);
		if (!argv[i + 1])
		{
			while (i >= 0)
				free(argv[i--]);
			free(argv);
			return (NULL);
		}
		i++;
	}
	argv[args_count + 1] = NULL;
	return (argv);
}

void	execute_command(t_table *table_aux, char **envp)
{
	int		args_count;
	char	**argv;

	args_count = count_args(table_aux->args);
	argv = duplicate_args(table_aux->cmd, table_aux->args, args_count);
	if (!argv || argv[0] == NULL)
		exit(1);
	execve_handler(argv, envp);
}
