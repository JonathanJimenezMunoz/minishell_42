/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:09:30 by david             #+#    #+#             */
/*   Updated: 2024/09/02 20:55:36 by dyanez-m         ###   ########.fr       */
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

static void free_redir(t_redir *redir)
{
    t_redir *current;
    t_redir *next;

    current = redir;
    while (current != NULL) {
        next = current->next;
        free(current->file); // Liberar la cadena de caracteres 'file'
        free(current); // Liberar el nodo 'redir' actual
        current = next;
    }
}

void free_table_aux(t_table_aux *aux)
{
    if (aux->args)
        free_double_array(aux->args);
    if (aux->redir)
        free_redir(aux->redir);
    if (aux->in_heredoc)
        free_double_array(aux->in_heredoc);
    // No es necesario establecer aux a NULL ya que es un puntero local
}

void free_table(t_table **table)
{
    t_table *current;
    t_table *next;

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
        free(current); // Liberar el nodo 'table' actual
        current = next;
    }
    *table = NULL; // Evitar el uso de punteros a memoria liberada
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
