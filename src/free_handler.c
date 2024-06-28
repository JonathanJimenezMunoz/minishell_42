/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:15:10 by david             #+#    #+#             */
/*   Updated: 2024/06/28 23:36:30 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void free_token_list(t_token **token)
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

void free_table(t_table **head)
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
        free(current);
        current = next;
    }
    *head = NULL;
}

void free_table_aux(t_table_aux *aux)
{
	if (aux->cmd)
		free(aux->cmd);
	if (aux->args)
		free(aux->args);
	if (aux->in_redir)
		free(aux->in_redir);
	if (aux->out_redir)
		free(aux->out_redir);
	if (aux->in_heredoc)
		free(aux->in_heredoc);
	if (aux->out_append)
		free(aux->out_append);
}
