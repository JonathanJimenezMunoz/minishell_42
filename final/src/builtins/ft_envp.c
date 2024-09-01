/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:18:15 by david             #+#    #+#             */
/*   Updated: 2024/09/01 17:18:35 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_envp(t_envp *envp)
{
	t_envp	*current;

	current = envp;
	while (current)
	{
		printf("\033[91m%s\033[0m=\033[93m%s\033[0m\n",
			current->key, current->value);
		current = current->next;
	}
	return (0);
}
