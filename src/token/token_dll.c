/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:23:25 by david             #+#    #+#             */
/*   Updated: 2024/06/25 22:39:34 by david            ###   ########.fr       */
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

void	token_clear(t_token **tokens)
{
	t_token	*tmp;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		tmp = (*tokens)->next;
		free((*tokens)->content);
		free(*tokens);
		*tokens = tmp;
	}
	*tokens = NULL;
}

void	token_print(t_token *tokens)
{
	while (tokens)
	{
		printf("content: %s\n", tokens->content);
		printf("type: %d\n", tokens->type);
		tokens = tokens->next;
	}
}

