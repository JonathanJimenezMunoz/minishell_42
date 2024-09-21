/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:09:46 by david             #+#    #+#             */
/*   Updated: 2024/09/21 21:06:25 by dyanez-m         ###   ########.fr       */
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
	while (envp[i] && ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
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

int	ft_heredoc_cmp(char *s1, char *s2)
{
	int	size_s1;
	int	size_s2;

	size_s1 = ft_strlen(s1) - 1;
	size_s2 = ft_strlen(s2);
	if (size_s1 != size_s2)
		return (1);
	if (ft_strncmp(s1, s2, size_s2) != 0)
		return (1);
	return (0);
}
