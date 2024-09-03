/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:09:30 by david             #+#    #+#             */
/*   Updated: 2024/09/03 15:32:14 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

void	free_redir(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	current = redir;
	while (current != NULL)
	{
		next = current->next;
		free(current->file);
		free(current);
		current = next;
	}
}

void	free_table_aux(t_table_aux *aux)
{
	if (aux->args)
		free_double_array(aux->args);
	if (aux->redir)
		free_redir(aux->redir);
	if (aux->in_heredoc)
		free_double_array(aux->in_heredoc);
}

void	free_table(t_table **table)
{
	t_table	*current;
	t_table	*next;

	current = *table;
	while (current != NULL)
	{
		next = current->next;
		if (current->args)
			free_double_array(current->args);
		if (current->redir)
			free_redir(current->redir);
		if (current->in_heredoc)
			free_double_array(current->in_heredoc);
		free(current);
		current = next;
	}
	*table = NULL;
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
