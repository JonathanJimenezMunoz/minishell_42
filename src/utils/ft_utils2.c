/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:09:46 by david             #+#    #+#             */
/*   Updated: 2024/09/01 19:10:48 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*join_strs(char **args)
{
	char	*result;
	char	*temp;
	int		i;

	i = 1;
	if (!args || !args[0])
		return (NULL);
	result = ft_strdup(args[0]);
	if (!result)
		return (NULL);
	while (args[i])
	{
		temp = ft_strjoin(result, " ");
		free(result);
		if (!temp)
			return (NULL);
		result = ft_strjoin(temp, args[i]);
		free(temp);
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}

int	count_double_str(char **args)
{
	int	count;

	count = 0;
	while (args && args[count] != NULL)
		count++;
	return (count);
}

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	return (envp[i] + 5);
}

int	is_valid_identifier(const char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
