/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:15:10 by david             #+#    #+#             */
/*   Updated: 2024/06/27 17:30:18 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void free_token_list(t_token *token)
{
    t_token *current = token;
    t_token *next;

    while (current != NULL)
    {
        next = current->next; // Guarda el siguiente nodo antes de liberar el actual
        free(current->content); // Libera el contenido del nodo
        free(current); // Libera el nodo
        current = next; // Avanza al siguiente nodo
    }	
}
