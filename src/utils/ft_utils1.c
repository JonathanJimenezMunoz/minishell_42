/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:29:47 by david             #+#    #+#             */
/*   Updated: 2024/08/21 17:29:31 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_clear_spaces(char **line)
{
	while (*line && !ft_isspace(**line))
		(*line)++;
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

void	ft_error(t_mini *mini, char *error, char *type)
{
	if (mini->status == 0)
	{
		printf("bash: %s `%s'\n", error, type);
		mini->status = 1;
	}
}

void	ft_error_aux(t_mini *mini, t_table_aux *aux, char *error, char *type)
{
	if (mini->status == 0)
	{
		printf("bash: %s `%s'\n", error, type);
		(void)aux;
		mini->status = 1;
	}
}
