/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:41:34 by david             #+#    #+#             */
/*   Updated: 2024/10/06 13:30:19 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ft_shlvl(t_envp *node)
{
	int	tmp;

	tmp = 0;
	if (!ft_strcmp(node->key, "SHLVL"))
	{
		tmp = ft_atoi(node->value);
		tmp++;
		free(node->value);
		node->value = ft_itoa(tmp);
	}
}

static t_envp	*create_new_node(char *env_str)
{
	char	*separator_pos;
	t_envp	*new_node;

	separator_pos = ft_strchr(env_str, '=');
	if (!separator_pos)
	{
		return (NULL);
	}
	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node)
	{
		return (NULL);
	}
	new_node->key = ft_strndup(env_str, separator_pos - env_str);
	new_node->value = ft_strdup(separator_pos + 1);
	new_node->next = NULL;
	ft_shlvl(new_node);
	return (new_node);
}

void	add_node_to_envp(t_envp **envp, t_envp *new_node)
{
	t_envp	*current;

	if (!*envp)
	{
		*envp = new_node;
	}
	else
	{
		current = *envp;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

void	envp_init(t_envp **envp, char **envp_list)
{
	int		i;
	t_envp	*new_node;

	i = 0;
	while (envp_list[i])
	{
		new_node = create_new_node(envp_list[i]);
		if (new_node)
		{
			add_node_to_envp(envp, new_node);
		}
		i++;
	}
}

char	*envp_get_value(t_envp *envp, char *key)
{
	t_envp	*current;

	current = envp;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}
