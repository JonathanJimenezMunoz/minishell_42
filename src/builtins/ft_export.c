/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:43:24 by david             #+#    #+#             */
/*   Updated: 2024/08/13 18:06:02 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	len_until_space(const char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != ' ')
		len++;
	return (len);
}

static void	parse_args(char *args, char **key, char **value)
{
	char	*separator;

	if (args[0] == '=')
	{
		separator = ft_strchr(args, '=');
		*key = ft_strdup("=");
		*value = ft_strndup(separator + 1, len_until_space(separator + 1));
	}
	else
	{
		separator = ft_strchr(args, '=');
		if (separator)
		{
			*separator = '\0';
			*key = ft_strdup(args);
			*value = ft_strndup(separator + 1, len_until_space(separator + 1));
		}
	}
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
	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (new_node)
	{
		new_node->key = key;
		new_node->value = value;
		new_node->next = NULL;
	}
	add_node_to_envp(envp, new_node);
	return (0);
}

//FALTAN FREES KEY VALUE
int	ft_export(char *args, t_envp **envp)
{
	char	*key;
	char	*value;
	t_envp	*envp_copy;

	key = NULL;
	value = NULL;
	if (args)
	{
		parse_args(args, &key, &value);
		if (!key || !value)
			return (-1);
		if (key[0] < 'A' || key[0] > 'z')
		{
			printf("bash: export: `%s': not a valid identifier\n", args);
			return (-1);
		}
		return (update_or_add_env(envp, key, value));
	}
	else
	{
		envp_copy = copy_envp_list(*envp);
		sort_envp(envp_copy);
		print_envp_declare(envp_copy);
		free_envp_list(envp_copy);
	}
	free(args);
	return (0);
}
