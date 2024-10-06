/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_shlvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:17:05 by dyanez-m          #+#    #+#             */
/*   Updated: 2024/10/06 13:33:22 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_shlvl(t_envp **mini)
{
	t_envp	*current;

	current = *mini;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, "SHLVL") == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

void	check_if_shlvl(t_envp **mini)
{
	t_envp	*current;
	t_envp	*new_node;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node)
		return ;
	current = *mini;
	if (check_shlvl(mini))
		return ;
	new_node->key = ft_strdup("SHLVL");
	new_node->value = ft_strdup("1");
	new_node->next = NULL;
	if (*mini == NULL)
	{
		*mini = new_node;
	}
	else
	{
		current = *mini;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}
