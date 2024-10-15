/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:51:40 by david             #+#    #+#             */
/*   Updated: 2024/10/15 19:06:21 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_individual_builtins(t_table *table_aux, t_mini *mini)
{
	if (!table_aux->args)
		return (-1);
	else if (ft_strncmp(table_aux->args[0], "unset", 6) == 0)
		return (ft_unset(table_aux->args, mini));
	else if (ft_strncmp(table_aux->args[0], "exit", 5) == 0)
		return (ft_exit(table_aux->args, mini));
	else if (ft_strncmp(table_aux->args[0], "export", 7) == 0)
		return (ft_export(table_aux->args, &(mini->envp)));
	else if (ft_strncmp(table_aux->args[0], "cd", 3) == 0)
		return (ft_cd(table_aux->args, mini->envp));
	else
		return (-1);
}

int	ft_non_individual_builtins(t_table *table_aux, t_mini *mini)
{
	if (!table_aux->args)
		return (-1);
	else if (ft_strncmp(table_aux->args[0], "echo", 6) == 0)
		return (ft_echo(table_aux->args));
	else if (ft_strncmp(table_aux->args[0], "env", 4) == 0)
		return (ft_envp(mini->envp, table_aux->args));
	else if (ft_strncmp(table_aux->args[0], "pwd", 4) == 0)
		return (ft_pwd(mini));
	else
		return (-1);
}
