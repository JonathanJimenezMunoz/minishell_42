/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_redir_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:46:52 by dyanez-m          #+#    #+#             */
/*   Updated: 2024/09/17 17:58:09 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	add_redir_end(t_table_aux *aux, char *file, int type)
{
	t_redir	*new_redir;
	t_redir	*last;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!new_redir)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
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
	t_redir	*current;
	t_redir	*new_list;
	t_redir	**ptr_to_next;

	current = head;
	new_list = NULL;
	ptr_to_next = &new_list;
	while (current != NULL)
	{
		*ptr_to_next = copy_redir_node(current);
		if (*ptr_to_next == NULL)
		{
			free_redir(new_list);
			return (NULL);
		}
		ptr_to_next = &((*ptr_to_next)->next);
		current = current->next;
	}
	return (new_list);
}

void	change_redir_node(t_mini *mini, t_redir *node, char *file, int type)
{
	t_table	*table;
	t_redir	*current;

	table = mini->table;
	while (table)
	{
		current = table->redir;
		while (current)
		{
			if (current == node)
			{
				printf("change_redir_node\n");
				free(mini->table->redir->file);
				printf("file: %s\n", file);
				mini->table->redir->file = ft_strdup(file);
				mini->table->redir->type = type;
				return ;
			}
			current = current->next;
		}
		table = table->next;
	}
	return ;
}
