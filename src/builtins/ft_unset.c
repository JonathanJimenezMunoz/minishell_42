/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:07:43 by david             #+#    #+#             */
/*   Updated: 2024/09/01 19:31:31 by david            ###   ########.fr       */
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

	if (!args || !args[1])
		return (0);
	key = args[1];
	return (remove_envp_node(key, mini));
}
