/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:18:15 by david             #+#    #+#             */
/*   Updated: 2024/09/06 17:06:31 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_envp(t_envp *envp, char **args)
{
	t_envp	*current;

	current = envp;
	if (args[1])
	{
		printf("env: %s: No such file or directory\n", args[1]);
		return (127);
	}
	while (current)
	{
		printf("\033[91m%s\033[0m=\033[93m%s\033[0m\n",
			current->key, current->value);
		current = current->next;
	}
	return (0);
}
