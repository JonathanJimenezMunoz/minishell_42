/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:09:30 by david             #+#    #+#             */
/*   Updated: 2024/08/31 17:25:08 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_token_list(t_token **token)
{
	t_token	*current;
	t_token	*next;

	current = *token;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*token = NULL;
}

void	free_table_aux(t_table_aux *aux)
{
	free_double_array(aux->args);
	free_double_array(aux->in_redir);
	free_double_array(aux->out_redir);
	free_double_array(aux->in_heredoc);
	free_double_array(aux->out_append);
	aux = NULL;
}
void	ft_free_all(t_mini *mini)
{
    free(mini->line);
	mini->line = NULL;
	free_token_list(&mini->tokens);
	mini->tokens = NULL;
	//free_table(&mini->table);
	mini->table = NULL;
	//free_envp(&mini->envp);
	mini->envp = NULL;
	//free_double_array(mini->exec_envp);
	mini->exec_envp = NULL;
	rl_clear_history();
}
