/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:24:08 by david             #+#    #+#             */
/*   Updated: 2024/09/01 20:29:47 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**copy_double_str(char **str)
{
	char	**new_str;
	int		i;

	i = 0;
	while (str[i])
		i++;
	new_str = malloc((i + 1) * sizeof(char *));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = ft_strdup(str[i]);
		if (!new_str[i])
		{
			free_double_array(new_str);
			return (NULL);
		}
		i++;
	}
	new_str[i] = NULL;
	return (new_str);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (0);
	return (-1);
}

int	ft_is_good_quote(char *line)
{
	int		i;
	char	quote_type;

	if (!line)
		return (-1);
	i = 0;
	if (line[i] == '\'' || line[i] == '\"')
		quote_type = line[i];
	else
		return (-2);
	i++;
	while (line[i])
	{
		if (line[i] == quote_type)
			return (i - 1);
		i++;
	}
	return (-1);
}

int ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return 1;
	if (n < 0)
		n = -n;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return len;
}

char	**ft_realloc_double_array(char **str, int new_size)
{
	char	**new_str;
	int		i;

	i = 0;
	new_str = (char **)malloc(new_size * sizeof(char *));
	if (!new_str)
		return (NULL);
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = NULL;
	free(str);
	return (new_str);
}
