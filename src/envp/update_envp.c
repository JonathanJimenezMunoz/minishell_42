/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:31:27 by dyanez-m          #+#    #+#             */
/*   Updated: 2024/09/21 21:06:48 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*ft_fixed_strjoin(char *s1, char *s2)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(s1, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s2);
	free(temp);
	return (result);
}

static char	**envp_to_array(t_envp *envp)
{
	t_envp	*current;
	char	**array;
	int		i;

	i = 0;
	current = envp;
	while (current)
	{
		i++;
		current = current->next;
	}
	array = malloc(sizeof(char *) * (i + 1));
	i = 0;
	current = envp;
	while (current)
	{
		array[i] = ft_fixed_strjoin(current->key, current->value);
		i++;
		current = current->next;
	}
	array[i] = NULL;
	return (array);
}

void	update_exec_envp_to_envp(t_mini *mini)
{
	if (mini->exec_envp)
		free_double_array(mini->exec_envp);
	mini->exec_envp = envp_to_array(mini->envp);
}
