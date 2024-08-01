/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:51:40 by david             #+#    #+#             */
/*   Updated: 2024/08/01 18:17:18 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	is_builtin_aux(t_table *table_aux, t_mini *mini)
{
	if (ft_strncmp(table_aux->cmd, "unset", 6) == 0)
	{
		ft_unset(table_aux->args, mini);
		return (0);
	}
	else if (ft_strncmp(table_aux->cmd, "env", 4) == 0)
	{
		ft_envp(mini->envp);
		return (0);
	}
	else if (ft_strncmp(table_aux->cmd, "exit", 5) == 0)
	{
		ft_exit(table_aux->args, mini);
		return (0);
	}
	return (1);
}

int	is_builtin(t_table *table_aux, t_mini *mini)
{
	if (ft_strncmp(table_aux->cmd, "echo", 5) == 0)
	{
		ft_echo(table_aux->args);
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
		return (0);
	}
	else if (ft_strncmp(table_aux->cmd, "export", 7) == 0)
	{
		ft_export(table_aux->args, &(mini->envp));		
		return (0);
	}
	else
		return (is_builtin_aux(table_aux, mini));
}
