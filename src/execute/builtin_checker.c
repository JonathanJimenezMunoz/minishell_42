/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:51:40 by david             #+#    #+#             */
/*   Updated: 2024/08/13 17:13:11 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_built_aux(t_table *table_aux, t_mini *mini)
{
	int	i;

	i = -1;
	if (ft_strncmp(table_aux->cmd, "unset", 6) == 0)
	{
		ft_unset(table_aux->args[0], mini);
		write_file(".err", 0);
		return (0);
	}
	else if (ft_strncmp(table_aux->cmd, "env", 4) == 0)
	{
		ft_envp(mini->envp);
		write_file(".err", 0);
		return (0);
	}
	else if (ft_strncmp(table_aux->cmd, "export", 7) == 0)
	{
		if (table_aux->args == NULL)
			ft_export(NULL, &(mini->envp));
		while (table_aux->args != NULL && table_aux->args[++i])
			ft_export(table_aux->args[i], &(mini->envp));
		write_file(".err", 0);
		return (0);
	}
	return (1);
}

int	ft_built(t_table *table_aux, t_mini *mini)
{
	if (ft_strncmp(table_aux->cmd, "echo", 5) == 0)
	{
		ft_echo(table_aux->args);
		write_file(".err", 0);
		return (0);
	}
	else if (ft_strncmp(table_aux->cmd, "cd", 3) == 0)
	{
		ft_cd(table_aux->args, mini->envp);
		return (0);
	}
	else if (ft_strncmp(table_aux->cmd, "pwd", 4) == 0)
	{
		ft_pwd();
		write_file(".err", 0);
		return (0);
	}
	else if (ft_strncmp(table_aux->cmd, "exit", 5) == 0)
	{
		ft_exit(table_aux->args, mini);
		return (0);
	}
	else
		return (ft_built_aux(table_aux, mini));
}

int	is_builtin(t_table *table_aux)
{
	if (table_aux->cmd == NULL)
		return (1);
	else if (ft_strncmp(table_aux->cmd, "unset", 6) == 0)
		return (0);
	else if (ft_strncmp(table_aux->cmd, "env", 4) == 0)
		return (0);
	else if (ft_strncmp(table_aux->cmd, "exit", 5) == 0)
		return (0);
	else if (ft_strncmp(table_aux->cmd, "export", 7) == 0)
		return (0);
	else if (ft_strncmp(table_aux->cmd, "echo", 5) == 0)
		return (0);
	else if (ft_strncmp(table_aux->cmd, "cd", 3) == 0)
		return (0);
	else if (ft_strncmp(table_aux->cmd, "pwd", 4) == 0)
		return (0);
	else
		return (1);
}

int	is_builtin_tech(t_table *table_aux)
{
	if (table_aux->cmd == NULL)
		return (0);
	else if (ft_strncmp(table_aux->cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(table_aux->cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(table_aux->cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(table_aux->cmd, "cd", 3) == 0)
		return (1);
	else
		return (0);
}
