/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:07:43 by david             #+#    #+#             */
/*   Updated: 2024/07/12 23:10:56 by david            ###   ########.fr       */
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
/*
void ft_unset(char *key, t_mini *mini) {
    t_envp *current;
    t_envp *prev;
    t_envp *to_free;

    current = mini->envp;
    prev = NULL;
    while (current) {
        if (!ft_strcmp(key, current->key)) {
            if (!prev)
                mini->envp = current->next;
            else
                prev->next = current->next;

            // Free the key and value strings before freeing the node itself
            free(current->key);
            free(current->value);

            to_free = current; // Store the current node to free after updating the links
            current = current->next; // Move to the next node before freeing

            free(to_free); // Now it's safe to free the node
            return;
        }
        prev = current;
        current = current->next;
    }*/