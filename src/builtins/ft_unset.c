/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:07:43 by david             #+#    #+#             */
/*   Updated: 2024/09/21 19:45:44 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	remove_envp_node(char *key, t_mini *mini)
{
	t_envp	*current;
	t_envp	*prev;

	current = mini->envp;
	prev = NULL;
	while (current)
	{
		if (!ft_strcmp(key, current->key))
		{
			if (!prev)
				mini->envp = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

int	ft_unset(char **args, t_mini *mini)
{
	char	*key;
	int		i;

	i = 1;
	if (!args || !args[1])
		return (0);
	while (args[i])
	{
		key = args[i];
		remove_envp_node(key, mini);
		i++;
	}
	return (0);
}
