/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 23:43:01 by david             #+#    #+#             */
/*   Updated: 2024/08/02 23:51:27 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	return (envp[i] + 5);
}

char *join_args(char **args)
{
	char *result;
	char *temp;
	int i;

	i = 1;
	if (!args || !args[0])
		return NULL;
	result = ft_strdup(args[0]);
	if (!result)
		return NULL;
	while(args[i])
	{
		temp = ft_strjoin(result, " ");
		free(result);
		if (!temp)
			return NULL;
		result = ft_strjoin(temp, args[i]);
		free(temp);
		if (!result)
			return (NULL);
	}
	return result;
}