/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:29:47 by david             #+#    #+#             */
/*   Updated: 2024/07/01 18:29:29 by david            ###   ########.fr       */
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

void ft_error(t_mini *mini, char *error, char *type)
{
	printf("msh>> %s %s\n", error, type);
	if (mini->tokens)
		free_token_list(&(mini->tokens));
	if (mini->table)
		free_table(&(mini->table));
	exit (1);
}

void ft_error_aux(t_mini *mini, t_table_aux *aux, char *error, char *type)
{
	printf("msh>> %s %s\n", error, type);
    free_table_aux(aux);
	if (mini->tokens)
		free_token_list(&(mini->tokens));
	if (mini->table)
		free_table(&(mini->table));
	exit (1);
}