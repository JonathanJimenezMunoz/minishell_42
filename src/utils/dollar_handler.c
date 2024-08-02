/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:52:39 by david             #+#    #+#             */
/*   Updated: 2024/08/02 16:58:54 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char  *ft_envp_key(char *line)
{
	int     size;
	int     i;
	char    *key;
	
	size = 0;
	i = 0;
	while (line[i] != '\0' && line[i] != ' ' && line[i] != '$')
	{
		size += 1;
		i++;
	}
	key = malloc(sizeof(char) * (size + 1));
	i = 0;
	while (line[i] != '\0' && line[i] != ' ' && line[i] != '$')
	{
		key[i] = line[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static int  ft_counter(char *line, int size, t_mini *mini)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while (i < size)
	{
		if (line[i] == '$')
		{
			i++;
			if (line[i] == '?')
			{
				counter += ft_strlen(mini->error);
				i++;
			}
			else if (line[i] != ' ')
			{
				counter += ft_strlen(envp_get_value(mini->envp,
								ft_envp_key(&(line[i])))) + 1;
				i += ft_strlen(ft_envp_key(&(line[i])));
			}
			else
				counter++;
		}
		else
			counter++;
		i++;
	}
	return (counter);
}

char	*ft_new_line(char *line, int size, t_mini *mini)
{
	char	*new_line;
	int		i;
	int		j;
	int		real_size;
	size_t	counter;
	char    *value;

	real_size = ft_counter(line, size, mini);
	new_line = malloc(sizeof(char) * (real_size + 10));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (line[i] == '$')
		{
			i++;
			if (line[i] == '?')
			{
				counter = 0;
				while (ft_strlen(mini->error) - 1 > counter)
				{
					new_line[j] = mini->error[counter];
					counter++;
					j++;
				}
				i++;
			}
			else if (line[i] != ' ')
			{
				counter = 0;
				value = envp_get_value(mini->envp,
								ft_envp_key(&(line[i])));
				while (ft_strlen(value) > counter)
				{
					new_line[j] = value[counter];
					counter++;
					j++;
				}
				i += ft_strlen(ft_envp_key(&(line[i])));
			}
			else
			{
				new_line[j] = line[i - 1];
				j++;
			}
		}
		else
		{
			new_line[j] = line[i];
			i++;
			j++;
		}
	}
	new_line[j] = '\0';
	return (new_line);
}
