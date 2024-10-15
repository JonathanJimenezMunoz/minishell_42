/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:47:13 by david             #+#    #+#             */
/*   Updated: 2024/10/15 17:30:24 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	swap(t_envp *a, t_envp *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void	sort_envp(t_envp *envp)
{
	int		swapped;
	t_envp	*ptr1;
	t_envp	*lptr;

	lptr = NULL;
	if (envp == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = envp;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

t_envp	*copy_envp_list(t_envp *envp)
{
	t_envp	*new_node;

	if (!envp)
		return (NULL);
	new_node = malloc(sizeof(t_envp));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(envp->key);
	new_node->value = ft_strdup(envp->value);
	new_node->next = copy_envp_list(envp->next);
	return (new_node);
}

void	free_envp_list(t_envp *envp)
{
	t_envp	*tmp;

	while (envp)
	{
		tmp = envp;
		envp = envp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	print_envp_declare(t_envp *envp)
{
	while (envp)
	{
		printf("declare -x \033[91m%s\033[0m=\"\033[93m%s\033[0m\"\n",
			envp->key, envp->value);
		envp = envp->next;
	}
}
