/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 22:32:54 by david             #+#    #+#             */
/*   Updated: 2024/07/31 18:50:14 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	init_aux(t_table_aux *aux)
{
	aux->cmd = NULL;
	aux->args = NULL;
	aux->in_redir = NULL;
	aux->out_redir = NULL;
	aux->out_append = NULL;
	aux->in_heredoc = NULL;
}

static void parse_while(t_mini *mini, t_table_aux *aux, int *first_word, t_token **current)
{
	if ((*current)->type == TOKEN_PIPE)
	{
		if ((*current)->next && (*current)->next->type == TOKEN_PIPE)
			ft_error_aux(mini, aux, 
				"syntax error near unexpected token", (*current)->next->content);
		*first_word = 1;
		add_node(&mini, aux);
		free_table_aux(aux);
		init_aux(aux);
	}
	parse_cmd_args(aux, first_word, current);
	parse_redir_in(mini, aux, current);
	parser_redir_out(mini, aux, current);
	parse_redir_append(mini, aux, current);
	parse_redir_heredoc(mini, aux, current);
}

int parser_token(t_mini *mini)
{
	t_token     *current;
	int         first_word;
	t_table_aux aux;

	first_word = 1;
	current = mini->tokens;
	if (!current)
		return (0);
	init_aux(&aux);
	if (current->type == TOKEN_PIPE)
		ft_error(mini, "syntax error near unexpected token", current->content);
	while (current)
	{
		parse_while(mini, &aux, &first_word, &current);
		current = current->next;
	}
	add_node(&mini, &aux);
	free_table_aux(&aux);
	return (0);
}
