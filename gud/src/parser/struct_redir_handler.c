/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_redir_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:46:52 by dyanez-m          #+#    #+#             */
/*   Updated: 2024/09/02 23:07:32 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	add_redir_end(t_table_aux *aux, char *file, int type)
{
	t_redir	*new_redir;
	t_redir	*last;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!new_redir)
		return ; // Manejar error de malloc aquí
	new_redir->file = ft_strdup(file);
	new_redir->type = type;
	new_redir->next = NULL;
	if (aux->redir == NULL)
	{
		aux->redir = new_redir;
	}
	else
	{
		last = aux->redir;
		while (last->next != NULL)
			last = last->next;
		last->next = new_redir;
	}
}

t_redir	*copy_redir_node(t_redir *node)
{
	t_redir	*new_node;

	new_node = (t_redir *)malloc(sizeof(t_redir));
	if (!new_node)
		return (NULL);
	new_node->file = ft_strdup(node->file);
	new_node->type = node->type;
	new_node->next = NULL;
	return (new_node);
}

t_redir	*copy_redir_list(t_redir *head)
{
	t_redir	*current = head;
	t_redir	*new_list = NULL;
	t_redir	**ptr_to_next = &new_list;

	while (current != NULL)
	{
		*ptr_to_next = copy_redir_node(current);
		if (*ptr_to_next == NULL)
		{
			// Manejar error de malloc aquí, posiblemente liberando la lista parcialmente copiada
			return (NULL);
		}
		ptr_to_next = &((*ptr_to_next)->next);
		current = current->next;
	}
	return (new_list);
}