/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:43:24 by david             #+#    #+#             */
/*   Updated: 2024/08/01 17:56:52 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	parse_args(char *args, char **key, char **value)
{
	char	*separator;

	separator = ft_strchr(args, '=');
	if (separator)
	{
		*separator = '\0';
		*key = ft_strdup(args);
		*value = ft_strdup(separator + 1);
	}
}

static t_envp *add_new_env_node(char *key, char *value)
{
	t_envp	*new_node;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (new_node)
	{
		new_node->key = key;
		new_node->value = value;
		new_node->next = NULL;
	}
	return (new_node);
}

static int	update_or_add_env(t_envp **envp, char *key, char *value)
{
	t_envp	*current;
	t_envp	*new_node;

	current = *envp;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			free(current->value);
			current->value = ft_strdup(value);
			free(key);
			return (0);
		}
		current = current->next;
	}
	new_node = add_new_env_node(key, value);
	add_node_to_envp(envp, new_node);
	return (0);
}

int ft_export(char *args, t_envp **envp)
{
	char	*key;
	char	*value;
	t_envp *envp_copy;

	key = NULL;
	value = NULL;
	if (args)
	{
		parse_args(args, &key, &value);
		if (!key || !value)
			return (-1);
		return (update_or_add_env(envp, key, value));
	}
	else
	{
		envp_copy = copy_envp_list(*envp);
		sort_envp(envp_copy);
		print_envp_declare(envp_copy);
		free_envp_list(envp_copy);
	}
	return (0);
}
