/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:15:10 by david             #+#    #+#             */
/*   Updated: 2024/08/21 17:28:20 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_token_list(t_token **token)
{
	t_token	*current;
	t_token	*next;

	current = *token;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*token = NULL;
}

void	free_envp(t_envp **envp)
{
	t_envp	*current;
	t_envp	*next;

	current = *envp;
	while (current != NULL)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*envp = NULL;
}

void	free_table(t_table **head)
{
	t_table	*current;
	t_table	*next;
	char	**args;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->cmd);
		if (current->args)
		{
			args = current->args;
			while (*args)
				free(*args++);
			free(current->args);
		}
		free(current->in_redir);
		free(current->out_redir);
		free(current->in_heredoc);
		free(current->out_append);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	free_table_aux(t_table_aux *aux)
{
	char	**args;

	free(aux->cmd);
	if (aux->args)
	{
		args = aux->args;
		while (*args)
			free(*args++);
		free(aux->args);
	}
	free(aux->in_redir);
	free(aux->out_redir);
	free(aux->in_heredoc);
	free(aux->out_append);
}

void	ft_free_all(t_mini *mini)
{
	free_token_list(&mini->tokens);
	free_table(&mini->table);
	free_envp(&mini->envp);
	if (mini->error)
	{
		free(mini->error);
		mini->error = NULL;
	}
	rl_clear_history();
}
