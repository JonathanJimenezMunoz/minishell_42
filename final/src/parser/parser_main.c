/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 22:32:54 by david             #+#    #+#             */
/*   Updated: 2024/08/31 18:31:09 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	init_aux(t_table_aux *aux)
{
	aux->args = NULL;
	aux->in_redir = NULL;
	aux->out_redir = NULL;
	aux->out_append = NULL;
	aux->in_heredoc = NULL;
}

static void	parse_while(t_mini *mini, t_table_aux *aux, t_token **current)
{
	if ((*current)->type == TOKEN_PIPE)
	{
		if (!(*current)->next)
			ft_error(mini, "syntax error near unexpected token",
				(*current)->content, 2);
		if ((*current)->next && (*current)->next->type == TOKEN_PIPE)
			ft_error(mini, "syntax error near unexpected token",
				(*current)->next->content, 2);
		add_node(&mini, aux);
		free_table_aux(aux);
		init_aux(aux);
	}
	parse_args(aux, current);
	parse_redir_in(mini, aux, current);
	parser_redir_out(mini, aux, current);
	parse_redir_append(mini, aux, current);
	parse_redir_heredoc(mini, aux, current);
}

int	parser_token(t_mini *mini)
{
	t_token		*current;
	t_table_aux	aux;

	current = mini->tokens;
	if (!current)
		return (0);
	init_aux(&aux);
	if (current->type == TOKEN_PIPE)
		ft_error(mini, "syntax error near unexpected token",
			current->content, 2);
	while (current)
	{
		parse_while(mini, &aux, &current);
		current = current->next;
	}
	add_node(&mini, &aux);
	free_table_aux(&aux);
	return (0);
}
