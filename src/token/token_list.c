

#include "../../headers/minishell.h"


t_token *token_new(char *content, t_token_type type)
{
	t_token *new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->type = type;
	new->next = NULL;
	return (new);
}

void append_node(t_token **head, t_token *new_token)
{
	if (*head == NULL) {
		*head = new_token;
	} else {
		t_token *temp = *head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new_token;
	}
}

int ft_add_token(t_token_type type, char **line, t_mini *mini, int size)
{
	t_token *token;
	char *content;
	int i;

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
	append_node(&(mini->tokens), token);
	return (0);
}

void token_print(t_token *tokens)
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