/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:52:39 by david             #+#    #+#             */
/*   Updated: 2024/08/03 00:52:32 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
static char  *ft_envp_key(char *line)
{
	int     i;
	char    *key;

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

static int  ft_counter(char *line, int size, t_mini *mini)
{
	int i;
	int counter;

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

char	*ft_new_line(char *line, int size, t_mini *mini)
{
	char	*new_line;
	int		i;
	int		j;
	int		real_size;
	size_t	counter;
	char    *value;

	real_size = ft_counter(line, size, mini);
	new_line = malloc(sizeof(char) * (real_size + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		counter = 0;
        if (line[i] == '$' && line[i + 1] == '?')
        {
            while (ft_strlen(mini->error) - 1 > counter)
                new_line[j++] = mini->error[counter++];
            i += 2;
        }
        else if (line[i] == '$' && line[i + 1] != ' ')
        {
            value = envp_get_value(mini->envp,
                            ft_envp_key(&(line[i])));
            while (ft_strlen(value) > counter)
                new_line[j++] = value[counter++];
            i += ft_strlen(ft_envp_key(&(line[i]))) + 1;
        }
        else
            new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
	return (new_line);
}
*/

static char  *ft_envp_key(char *line)
{
	int     i;
	char    *key;

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

static int  ft_counter(char *line, int size, t_mini *mini)
{
	int i;
	int counter;

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
/*

static char	*ft_new_line_aux(char *new_line, t_mini *mini, int *i, int *j)
{
	size_t	counter;
	char    *value;
	
	counter = 0;
	if (line[(*i)] == '$' && line[(*i) + 1] == '?')
	{
		while (ft_strlen(mini->error) - 1 > counter)
			new_line[(*j)++] = mini->error[counter++];
		(*i) += 2;
	}
	else if (line[(*i)] == '$' && line[(*i) + 1] != ' ')
	{
		value = envp_get_value(mini->envp,
						ft_envp_key(&(line[(*i)])));
		while (ft_strlen(value) > counter)
			new_line[(*j)++] = value[counter++];
		(*i) += ft_strlen(ft_envp_key(&(line[(*i)]))) + 1;
	}
	else
		new_line[(*j)++] = line[(*i)++];
	return (new_line);
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
        new_line = ft_new_line_aux(new_line, mini, &i, &j);
	new_line[j] = '\0';
	return (new_line);
}*/

static int	handle_env_variable(char **new_line, int *j,
			char *line, t_mini *mini)
{
	int		i;
	size_t	counter;
	char	*value;

	i = 0;
	printf("line: %s\n", line);
	printf("key: %s\n", ft_envp_key(line));
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
