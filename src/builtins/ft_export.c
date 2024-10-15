/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:43:24 by david             #+#    #+#             */
/*   Updated: 2024/10/15 19:06:35 by dyanez-m         ###   ########.fr       */
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

static void	parse_args_export(char *args, char **key, char **value)
{
	char	*separator;

	separator = ft_strchr(args, '=');
	if (separator)
	{
		if (args[0] == '=')
			*key = ft_strdup("=");
		else
		{
			*separator = '\0';
			*key = ft_strdup(args);
		}
		*value = ft_strndup(separator + 1, len_until_space(separator + 1));
	}
	else
		*key = ft_strdup(args);
}

int	update_or_add_env(t_envp **envp, char *key, char *value)
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
			return (0);
		}
		current = current->next;
	}
	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (new_node)
	{
		new_node->key = ft_strdup(key);
		new_node->value = ft_strdup(value);
		new_node->next = NULL;
	}
	add_node_to_envp(envp, new_node);
	return (0);
}

static int	ft_export_aux(char *args, t_envp **envp)
{
	char	*key;
	char	*value;
	int		result;

	key = NULL;
	value = NULL;
	parse_args_export(args, &key, &value);
	if (!is_valid_identifier(key))
	{
		ft_error_export(args);
		free(key);
		if (value)
			free(value);
		return (1);
	}
	if (!value)
	{
		free(key);
		return (0);
	}
	result = update_or_add_env(envp, key, value);
	free(key);
	free(value);
	return (result);
}

int	ft_export(char **args, t_envp **envp)
{
	t_envp	*envp_copy;
	int		i;
	int		err;

	err = 0;
	i = 0;
	if (args && (args[1] == NULL || args[1][0] == '\0'))
	{
		envp_copy = copy_envp_list(*envp);
		sort_envp(envp_copy);
		print_envp_declare(envp_copy);
		free_envp_list(envp_copy);
	}
	else
	{
		while (args && args[++i])
		{
			if (ft_export_aux(args[i], envp) != 0)
				err = 1;
		}
	}
	return (err);
}
