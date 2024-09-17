/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:27:38 by david             #+#    #+#             */
/*   Updated: 2024/09/17 17:57:43 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_token	*token_new(char *content, t_token_type type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->type = type;
	new->next = NULL;
	return (new);
}

static void	append_node(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (*head == NULL)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_token;
	}
}

int	ft_add_token(t_token_type type, char **line, t_mini *mini, int size)
{
	t_token	*token;
	char	*content;
	int		i;

	content = (char *)malloc(sizeof(char) * (size + 1));
	i = 0;
	while (size > i)
	{
		content[i] = **line;
		(*line)++;
		i++;
	}
	content[i] = '\0';
	if (type == TOKEN_QUOTES_EMPTY)
		token = token_new("", TOKEN_QUOTES_EMPTY);
	else if (content[0] == '\0')
		token = token_new(NULL, TOKEN_EMPTY);
	else
		token = token_new(content, type);
	free(content);
	if (!token)
		return (-1);
	append_node(&(mini->tokens), token);
	return (0);
}

void	token_print(t_token *tokens)
{
	while (tokens)
	{
		printf("Token:\n");
		if (tokens->content)
			printf("content: %s\n", tokens->content);
		else
			printf("content: NULL\n");
		printf("type: %d\n", tokens->type);
		tokens = tokens->next;
	}
}

void	join_token(t_token **tokens)
{
	t_token	*next;
	t_token	*curr;
	char	*joined;

	curr = *tokens;
	while (curr && curr->next)
	{
		next = curr->next;
		if ((curr->type == TOKEN_WORD || curr->type == TOKEN_QUOTES_EMPTY)
			&& (next->type == TOKEN_WORD || next->type == TOKEN_QUOTES_EMPTY)
			&& (curr->type != TOKEN_QUOTES_EMPTY
				|| next->type != TOKEN_QUOTES_EMPTY))
		{
			joined = ft_strjoin(curr->content, next->content);
			free(curr->content);
			curr->content = joined;
			curr->type = TOKEN_WORD;
			curr->next = next->next;
			free(next->content);
			free(next);
		}
		else
			curr = curr->next;
	}
}
