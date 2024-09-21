/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:52:39 by david             #+#    #+#             */
/*   Updated: 2024/09/21 18:37:08 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*ft_envp_key(char *line)
{
	int		i;
	char	*key;

	i = 0;
	while (line[i] != '\"' && line[i] != '\'' && line[i] != ' '
		&& line[i] != '$' && line[i] != '\0' && line[i] != '\n')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (line[i] != '\"' && line[i] != '\'' && line[i] != ' '
		&& line[i] != '$' && line[i] != '\0' && line[i] != '\n')
	{
		key[i] = line[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static int	ft_counter(char *line, int size, t_mini *mini)
{
	int		i;
	int		counter;
	char	*key;

	i = 0;
	counter = 0;
	while (i < size)
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			counter += ft_intlen(mini->exit_status);
			i++;
		}
		else if (line[i] == '$' && line[i + 1] != ' ')
		{
			key = ft_envp_key(&(line[i + 1]));
			counter += ft_strlen(envp_get_value(mini->envp, key)) + 1;
			i += ft_strlen(key);
			free(key);
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
	char	*key;
	size_t	len_value;

	i = 0;
	key = ft_envp_key(line);
	value = envp_get_value(mini->envp, key);
	counter = 0;
	if (value)
		len_value = ft_strlen(value);
	else
		len_value = 0;
	while (len_value > counter)
		(*new_line)[(*j)++] = value[counter++];
	i += ft_strlen(key) + 1;
	free(key);
	return (i);
}

static int	handle_error_variable(char **new_line, int *j, t_mini *mini)
{
	size_t	counter;
	char	*exit_status;

	counter = 0;
	exit_status = ft_itoa(mini->exit_status);
	while (ft_strlen(exit_status) > counter)
		(*new_line)[(*j)++] = exit_status[counter++];
	free(exit_status);
	return (2);
}

char	*ft_new_line(char *l, int size, t_mini *mini)
{
	char	*new_line;
	int		i;
	int		j;
	int		real_size;

	real_size = ft_counter(l, size, mini);
	new_line = malloc(sizeof(char) * (real_size + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (l[i] == '$' && l[i + 1] == '?')
			i += handle_error_variable(&new_line, &j, mini);
		else if (l[i] == '$' && ft_isspace(l[i + 1]) && l[i + 1]
			&& l[i + 1] != '\"')
			i += handle_env_variable(&new_line, &j, &(l[i + 1]), mini);
		else
			new_line[j++] = l[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}
