/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:23:25 by david             #+#    #+#             */
/*   Updated: 2024/06/28 22:49:44 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_token	*token_new(char *content, int type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	token_add_back(t_token **tokens, t_token *new)
{
	t_token	*last;

	if (!tokens || !new)
		return ;
	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	last = *tokens;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}



void	token_print(t_token *tokens)
{
	while (tokens)
	{
		printf("Token:\n");
		printf("content: %s\n", tokens->content);
		printf("type: %d\n", tokens->type);
		tokens = tokens->next;
	}
}

int	ft_add_token(t_token_type type, char **line, t_mini*mini, int size)
{
	t_token	*token;
	char	*content;
	int 	i;

	content = (char *)malloc(sizeof(char) * (size + 1));
	i = 0;
	while (size > i)
	{
		content[i] = **line;
		(*line)++;
		i++;
	}
	content[i] = '\0';
	token = token_new(content, type);
	free(content);
	if (!token)
		return (-1);
	
	token_add_back(&(mini->tokens), token);
	return (0);
}
