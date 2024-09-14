/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 22:15:22 by david             #+#    #+#             */
/*   Updated: 2024/09/14 19:19:20 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_table	*create_node(t_table_aux *aux)
{
	t_table	*new_node;

	new_node = (t_table *)malloc(sizeof(t_table));
	if (!new_node)
		return (NULL);
	if (aux->args != NULL)
		new_node->args = copy_double_str(aux->args);
	else
		new_node->args = NULL;
	if (aux->redir != NULL)
		new_node->redir = copy_redir_list(aux->redir);
	else
		new_node->redir = NULL;
	new_node->next = NULL;
	return (new_node);
}

static void	append_node(t_table **head, t_table *new_node)
{
	t_table	*current;

	if (!*head)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

int	add_node(t_mini **head, t_table_aux *aux)
{
	t_table	*new_node;

	new_node = create_node(aux);
	if (!new_node)
		return (-1);
	append_node(&((*head)->table), new_node);
	return (0);
}
