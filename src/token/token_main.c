/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:24:28 by david             #+#    #+#             */
/*   Updated: 2024/08/21 17:21:30 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	tokenize_quote_aux(char **line, t_mini *mini, int size)
{
	char	*tmp;
	int		recover;

	recover = 0;
	tmp = ft_new_line(*line, size, mini);
	recover = ft_strlen(tmp);
	ft_add_token(TOKEN_WORD, &tmp, mini, ft_strlen(tmp));
	tmp -= recover;
	free(tmp);
	*line += size;
}

static void	tokenize_quote(char **line, t_mini *mini)
{
	int	size;
	int	is_simple;

	is_simple = 0;
	size = ft_is_good_quote(*line);
	if (size > 0)
	{
		if ((*line)[0] == '\'')
			is_simple = 1;
		*line += 1;
		if (is_simple)
			ft_add_token(TOKEN_WORD, line, mini, size);
		else
			tokenize_quote_aux(line, mini, size);
		*line += 1;
	}
	else if (size == -1)
	{
		printf("Error: Comillas mal cerradas\n");
		mini->status = 1;
	}
	else if (size == 0)
		*line += 2;
}

static void	tokenize_redir(char **line, t_mini *mini)
{
	if (!ft_strncmp(*line, "<", 1) || !ft_strncmp(*line, ">", 1)
		|| !ft_strncmp(*line, "|", 1))
	{
		if (ft_redir_type(line, mini) == -1)
		{
			printf("Error: Caracter no reconocido\n");
			mini->status = 1;
		}
	}
}

static void	tokenize_word(char **line, t_mini *mini)
{
	int		i;
	char	*tmp;
	int		recover;

	i = 0;
	while ((*line)[i] != '<' && (*line)[i] != '>' && (*line)[i] != '|'
		&& (*line)[i] != '\'' && (*line)[i] != '\"' && ft_isspace((*line)[i])
		&& (*line)[i] != '\0')
	{
		i++;
	}
	if (i > 0)
	{
		tmp = ft_new_line(*line, i, mini);
		recover = ft_strlen(tmp);
		ft_add_token(TOKEN_WORD, &tmp, mini, ft_strlen(tmp));
		tmp -= recover;
		free(tmp);
		*line += i;
	}
}

int	tokenize_line(char *line, t_mini *mini)
{
	read_file(".err", mini);
	while (line != NULL && *line != 0 && mini->status != 1)
	{
		ft_clear_spaces(&line);
		tokenize_quote(&line, mini);
		tokenize_redir(&line, mini);
		tokenize_word(&line, mini);
	}
	return (0);
}
