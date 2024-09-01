/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:09:30 by david             #+#    #+#             */
/*   Updated: 2024/09/01 19:35:26 by david            ###   ########.fr       */
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

void	free_table_aux(t_table_aux *aux)
{
	if (aux->args)
		free_double_array(aux->args);
	if (aux->in_redir)
		free_double_array(aux->in_redir);
	if (aux->out_redir)
		free_double_array(aux->out_redir);
	if (aux->in_heredoc)
		free_double_array(aux->in_heredoc);
	if (aux->out_append)
		free_double_array(aux->out_append);
	if (aux->last_out_redir)
		free(aux->last_out_redir);
	aux = NULL;
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
		if (current->in_redir)
			free_double_array(current->in_redir);
		if (current->out_redir)
			free_double_array(current->out_redir);
		if (current->in_heredoc)
			free_double_array(current->in_heredoc);
		if (current->out_append)
			free_double_array(current->out_append);
		if (current->last_out_redir)
			free(current->last_out_redir);
		free(current);
		current = next;
	}
	*table = NULL;
}

static void	free_envp(t_envp **envp)
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
void	ft_free_all(t_mini *mini)
{
	if (mini->line)
    	free(mini->line);
	mini->line = NULL;
	if (mini->tokens)
		free_token_list(&mini->tokens);
	mini->tokens = NULL;
	if (mini->table)
		free_table(&mini->table);
	mini->table = NULL;
	if (mini->envp)
		free_envp(&mini->envp);
	mini->envp = NULL;
	if (mini->exec_envp)
		free_double_array(mini->exec_envp);
	mini->exec_envp = NULL;
	rl_clear_history();
}
