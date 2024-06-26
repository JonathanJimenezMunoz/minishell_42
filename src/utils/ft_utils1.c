/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:29:47 by david             #+#    #+#             */
/*   Updated: 2024/06/26 23:53:45 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void ft_clear_spaces(char **line)
{
    while (*line && !ft_isspace(**line))
        (*line)++;
}

int ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (0);
	return (-1);
}

int ft_is_good_quote(char *line)
{
    int i;
    char quote_type;

    if (!line)
        return (-1);

    i = 0;
    if (line[i] == '\'' || line[i] == '\"')
        quote_type = line[i];
    else
        return (0);
    i++;
    while (line[i])
    {
        if (line[i] == quote_type)
            return (i);
        i++;
    }
    return (-1);
}

