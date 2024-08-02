/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:15:10 by david             #+#    #+#             */
/*   Updated: 2024/08/03 01:10:25 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_token_list(t_token **token)
{
    t_token *current = *token;
    t_token *next;

    while (current != NULL)
    {
        next = current->next;
        free(current->content);
        free(current);
        current = next;
    }	
}

void	free_table(t_table **head)
{
    t_table *current;
    t_table *next;

	current = *head;
    while (current != NULL)
	{
        next = current->next;
		if (current->cmd)
            free(current->cmd);
		if (current->args)
        	free(current->args);
        if (current->in_redir)
			free(current->in_redir);
        if (current->out_redir)
			free(current->out_redir);
        if (current->in_heredoc)
			free(current->in_heredoc);
        if (current->out_append)
			free(current->out_append);
        free(current);
        current = next;
    }
    *head = NULL;
}

void	free_table(t_table **head)
{
    t_table *current;
    t_table *next;

    current = *head;
    while (current != NULL)
    {
        next = current->next;
        free(current->cmd);
        if (current->args)
        {
            char **args = current->args;
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
    free(aux->cmd);
    if (aux->args)
    {
        char **args = aux->args;
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
	free_table(&(mini->table));
	free_envp(&(mini->envp));
}
