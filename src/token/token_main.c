/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:24:28 by david             #+#    #+#             */
/*   Updated: 2024/06/27 17:20:11 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int ft_redir_type(char **line, t_mini *mini)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (ft_add_token(TOKEN_REDIR_DELIMITER, line, mini, 2));
	else if (!ft_strncmp(*line, ">>", 2))
		return (ft_add_token(TOKEN_REDIR_APPEND, line, mini, 2));
	else if (!ft_strncmp(*line, "<", 1))
		return (ft_add_token(TOKEN_REDIR_IN, line, mini, 1));
	else if (!ft_strncmp(*line, ">", 1))
		return (ft_add_token(TOKEN_REDIR_OUT, line, mini, 1));
	else
		return (ft_add_token(TOKEN_PIPE, line, mini, 1));
}

static void tokenize_quote(char **line, t_mini *mini)
{
	int size;

	size = ft_is_good_quote(*line);
	if (size > 0)
	{
		*line += 1;
		ft_add_token(TOKEN_WORD, line, mini, size);
		*line += 1;
	}
	else if (size == -1)
	{
		mini->error = -1;
		printf("Error: Comillas mal cerradas\n");
		// Faltan los frees
		exit(1);
	}
	else if (size == 0)
		*line += 2;
}

static void tokenize_redir(char **line, t_mini *mini)
{
	if (!ft_strncmp(*line, "<", 1) || !ft_strncmp(*line, ">", 1)
		|| !ft_strncmp(*line, "|", 1))
	{
		mini->error = ft_redir_type(line, mini);
		if (mini->error == -1)
		{
			printf("Error: Caracter no reconocido\n");
			// Faltan los frees
			exit(1);
		}
	}
}

static void tokenize_word(char **line, t_mini *mini)
{
	int i;

	i = 0;
	while ((*line)[i] != '<' && (*line)[i] != '>' && (*line)[i] != '|' 
		&& (*line)[i] != '\'' && (*line)[i] != '\"' && ft_isspace((*line)[i])
		&& (*line)[i] != '\0')
	{
		i++;
	}
	if (i > 0)
		ft_add_token(TOKEN_WORD, line, mini, i);

}
int tokenize_line(char *line, t_mini *mini)
{
	while (line != NULL && *line != 0)
	{
		ft_clear_spaces(&line);
		// TENER EN CUENTA $ Y $?
		tokenize_quote(&line, mini);
		tokenize_redir(&line, mini);
		tokenize_word(&line, mini);
	}
	return (0);
}
