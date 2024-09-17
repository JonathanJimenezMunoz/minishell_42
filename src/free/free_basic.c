/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:27:49 by david             #+#    #+#             */
/*   Updated: 2024/09/03 15:21:13 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_double_array(char **str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_all(t_mini *mini)
{
	if (mini->line)
		free(mini->line);
	mini->line = NULL;
	if (mini->tokens)
		free_token_list(&mini->tokens);
	mini->tokens = NULL;
	if (mini->table)
		free_table(&mini->table);
	mini->table = NULL;
	if (mini->envp)
		free_envp(&mini->envp);
	mini->envp = NULL;
	if (mini->exec_envp)
		free_double_array(mini->exec_envp);
	mini->exec_envp = NULL;
	rl_clear_history();
}
