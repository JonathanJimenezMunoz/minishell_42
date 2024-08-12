/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 22:15:22 by david             #+#    #+#             */
/*   Updated: 2024/08/12 20:14:22 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	create_node_aux(t_table *new_node, t_table_aux *aux)
{
	if (aux->out_redir != NULL)
		new_node->out_redir = ft_strdup(aux->out_redir);
	else
		new_node->out_redir = NULL;
	if (aux->in_heredoc != NULL)
		new_node->in_heredoc = ft_strdup(aux->in_heredoc);
	else
		new_node->in_heredoc = NULL;
	if (aux->out_append != NULL)
		new_node->out_append = ft_strdup(aux->out_append);
	else
		new_node->out_append = NULL;
}

char	**duplicate_args(char **args)
{
	int		count;
	char	**new_args;

	count = 0;
	while (args[count] != NULL)
		count++;
	new_args = (char **)malloc((count + 1) * sizeof(char *));
	if (!new_args)
		return (NULL);
	count = 0;
	while (args[count] != NULL)
	{
		new_args[count] = ft_strdup(args[count]);
		if (!new_args[count])
		{
			while (count > 0)
				free(new_args[--count]);
			free(new_args);
			return (NULL);
		}
		count++;
	}
	new_args[count] = NULL;
	return (new_args);
}

t_table	*create_node(t_table_aux *aux)
{
	t_table	*new_node;

	new_node = (t_table *)malloc(sizeof(t_table));
	if (!new_node)
		return (NULL);
	if (aux->cmd != NULL)
		new_node->cmd = ft_strdup(aux->cmd);
	else
		new_node->cmd = NULL;
	if (aux->args != NULL)
		new_node->args = duplicate_args(aux->args);
	else
		new_node->args = NULL;
	if (aux->in_redir != NULL)
		new_node->in_redir = ft_strdup(aux->in_redir);
	else
		new_node->in_redir = NULL;
	create_node_aux(new_node, aux);
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
