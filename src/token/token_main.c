/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:24:28 by david             #+#    #+#             */
/*   Updated: 2024/06/26 18:09:59 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_add_token(t_token_type type, char **line_ptr, t_token **token_list)
{
	t_token	*token;

	token = ft_new_token(NULL, type);
	if (!token)
		return (0);
	ft_token_list_add_back(token_list, token);
	(*line_ptr)++;
	if (type == T_DLESS || type == T_DGREAT || type == T_OR || type == T_AND)
		(*line_ptr)++;
	return (1);
}

int ft_separator_type(char *line, t_mini *mini)
{
	if (!ft_strncmp(line, "<<", 2))
		return (ft_append_separator(T_DLESS, line_ptr, token_list) && 1);
	else if (!ft_strncmp(line, ">>", 2))
		return (ft_append_separator(T_DGREAT, line_ptr, token_list) && 1);
	else if (!ft_strncmp(line, "<", 1))
		return (ft_append_separator(T_LESS, line_ptr, token_list) && 1);
	else if (!ft_strncmp(line, ">", 1))
		return (ft_append_separator(T_GREAT, line_ptr, token_list) && 1);
	else
		return (ft_append_separator(T_PIPE, line_ptr, token_list) && 1);
}


int tokenize_line(char *line, t_mini *mini)
{
	
	while (line != NULL || *line != NULL)
	{
		clear_spaces(&line);
		// TENER EN CUENTA $ Y $?
		if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
			|| !ft_strncmp(line, "|", 1))
			mini->error = (!ft_separator_type(line, mini) && 1);

		//Debe saltar dentro de cada funcion
	}
	return (0);
}