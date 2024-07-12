/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:18:15 by david             #+#    #+#             */
/*   Updated: 2024/07/11 23:44:19 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_envp(t_envp *envp)
{
	t_envp	*current;

	current = envp;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}