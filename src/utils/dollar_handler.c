/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:52:39 by david             #+#    #+#             */
/*   Updated: 2024/08/13 16:08:05 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*ft_envp_key(char *line)
{
	int		i;
	char	*key;

	i = 0;
	while (line[i] != '\"' && line[i] != '\'' && line[i] != ' '
		&& line[i] != '$' && line[i] != '\0')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (line[i] != '\"' && line[i] != '\'' && line[i] != ' '
		&& line[i] != '$' && line[i] != '\0')
	{
		key[i] = line[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static int	ft_counter(char *line, int size, t_mini *mini)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (i < size)
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			counter += ft_strlen(mini->error);
			i++;
		}
		else if (line[i] == '$' && line[i + 1] != ' ')
		{
			counter += ft_strlen(envp_get_value(mini->envp,
						ft_envp_key(&(line[i])))) + 1;
			i += ft_strlen(ft_envp_key(&(line[i])));
		}
		else
			counter++;
		i++;
	}
	return (counter);
}

static int	handle_env_variable(char **new_line, int *j,
			char *line, t_mini *mini)
{
	int		i;
	size_t	counter;
	char	*value;

	i = 0;
	value = envp_get_value(mini->envp, ft_envp_key(line));
	counter = 0;
	while (ft_strlen(value) > counter)
		(*new_line)[(*j)++] = value[counter++];
	i += ft_strlen(ft_envp_key(line)) + 1;
	return (i);
}

static void	handle_error_variable(char **new_line, int *j, t_mini *mini)
{
	size_t	counter;

	counter = 0;
	while (ft_strlen(mini->error) - 1 > counter)
		(*new_line)[(*j)++] = mini->error[counter++];
}

char	*ft_new_line(char *line, int size, t_mini *mini)
{
	char	*new_line;
	int		i;
	int		j;
	int		real_size;

	real_size = ft_counter(line, size, mini);
	new_line = malloc(sizeof(char) * (real_size + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			handle_error_variable(&new_line, &j, mini);
			i += 2;
		}
		else if (line[i] == '$' && line[i + 1] != ' ')
			i += handle_env_variable(&new_line, &j, &(line[i + 1]), mini);
		else
			new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}