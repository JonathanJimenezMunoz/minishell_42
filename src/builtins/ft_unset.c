/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:07:43 by david             #+#    #+#             */
/*   Updated: 2024/08/02 23:15:49 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_unset(char *key, t_mini *mini)
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
			return ;
		}
		prev = current;
		current = current->next;
	}
}
