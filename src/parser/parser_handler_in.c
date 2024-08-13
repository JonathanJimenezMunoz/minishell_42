/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:26:57 by david             #+#    #+#             */
/*   Updated: 2024/08/13 17:36:38 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	parser_redir_in_aux(t_mini *mini,
	t_table_aux *aux, t_token **current)
{
	if (aux->in_heredoc)
	{
		free(aux->in_heredoc);
		aux->in_heredoc = NULL;
	}
	if (aux->in_redir)
	{
		open_file(aux->in_redir, O_RDONLY, 0644, mini);
		free(aux->in_redir);
		aux->in_redir = NULL;
	}
	aux->in_redir = ft_strdup((*current)->content);
}

static void	parser_redir_heredoc_aux(t_mini *mini,
	t_table_aux *aux, t_token **current)
{
	if (aux->in_redir)
	{
		open_file(aux->in_redir, O_RDONLY, 0644, mini);
		free(aux->in_redir);
		aux->in_redir = NULL;
	}
	if (aux->in_heredoc)
	{
		free(aux->in_heredoc);
		aux->in_heredoc = NULL;
	}
	aux->in_heredoc = ft_strdup((*current)->content);
}

void	parse_redir_in(t_mini *mini, t_table_aux *aux, t_token **current)
{
	if ((*current)->type == TOKEN_REDIR_IN)
	{
		if (!(*current)->next)
		{
			ft_error_aux(mini, aux,
				"syntax error near unexpected token", "newline");
			return ;
		}
		*current = (*current)->next;
		if ((*current)->type != TOKEN_WORD)
		{
			ft_error_aux(mini, aux,
				"syntax error near unexpected token", (*current)->content);
			return ;
		}
		parser_redir_in_aux(mini, aux, current);
	}
}

void	parse_redir_heredoc(t_mini *mini, t_table_aux *aux, t_token **current)
{
	if ((*current)->type == TOKEN_REDIR_DELIMITER)
	{
		if (!(*current)->next)
		{
			ft_error_aux(mini, aux,
				"syntax error near unexpected token", "newline");
			return ;
		}
		*current = (*current)->next;
		if ((*current)->type != TOKEN_WORD)
		{
			ft_error_aux(mini, aux,
				"syntax error near unexpected token", (*current)->content);
			return ;
		}
		parser_redir_heredoc_aux(mini, aux, current);
	}
}
