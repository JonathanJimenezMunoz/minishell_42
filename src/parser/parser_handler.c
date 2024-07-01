/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:14:05 by david             #+#    #+#             */
/*   Updated: 2024/07/01 19:35:47 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../headers/minishell.h"


void parse_cmd_args(t_table_aux *aux, int *first_word, t_token **current)
{
	if (*first_word == 1 && (*current)->type == TOKEN_WORD)
	{
		aux->cmd = ft_strdup((*current)->content);
		*first_word = 0;
	}
	else if ((*current)->type == TOKEN_WORD)
	{
		if (aux->args)
			aux->args = ft_strjoin2(aux->args, " ");
		if (!aux->args)
			aux->args = ft_strdup((*current)->content);
		else
			aux->args = ft_strjoin2(aux->args, (*current)->content);
	}
}

void parse_redir_in(t_mini *mini, t_table_aux *aux, t_token **current)
{
	if ((*current)->type == TOKEN_REDIR_IN)
	{
		if ((*current)->next)
			*current = (*current)->next;
		if ((*current)->type != TOKEN_WORD)
			ft_error_aux(mini, aux, 
				"syntax error near unexpected token", (*current)->content);
		if (aux->in_heredoc)
		{
			free(aux->in_heredoc);
			aux->in_heredoc = NULL;
		}
		if (aux->in_redir)
		{
			free(aux->in_redir);
			aux->in_redir = NULL;
		}
		aux->in_redir = ft_strdup((*current)->content);
	}
}

void parser_redir_out(t_mini *mini, t_table_aux *aux, t_token **current)
{
	if ((*current)->type == TOKEN_REDIR_OUT)
	{
		if (!(*current)->next)
			ft_error_aux(mini, aux, 
				"syntax error near unexpected token", "newline");
		*current = (*current)->next;
		if ((*current)->type != TOKEN_WORD)
			ft_error_aux(mini, aux, 
				"syntax error near unexpected token", (*current)->content);
		if (aux->out_append)
		{
			free(aux->out_append);
			aux->out_append = NULL;
		}
		if (aux->out_redir)
		{
			free(aux->out_redir);
			aux->out_redir = NULL;
		}
		aux->out_redir = ft_strdup((*current)->content);
	}
}

void parse_redir_append(t_mini *mini, t_table_aux *aux, t_token **current)
{
	if ((*current)->type == TOKEN_REDIR_APPEND)
	{
		if (!(*current)->next)
			ft_error_aux(mini, aux, 
				"syntax error near unexpected token", "newline");
		*current = (*current)->next;
		if ((*current)->type != TOKEN_WORD)
			ft_error_aux(mini, aux, 
				"syntax error near unexpected token", (*current)->content);
		if (aux->out_redir)
		{
			free(aux->out_redir);
			aux->out_redir = NULL;
		}
		if (aux->out_append)
		{
			free(aux->out_append);
			aux->out_append = NULL;
		}
		aux->out_append = ft_strdup((*current)->content);
	}
}

void parse_redir_heredoc(t_mini *mini, t_table_aux *aux, t_token **current)
{
	if ((*current)->type == TOKEN_REDIR_DELIMITER)
	{
		if (!(*current)->next)
			ft_error_aux(mini, aux, 
				"syntax error near unexpected token", "newline");
		*current = (*current)->next;
		if ((*current)->type != TOKEN_WORD)
			ft_error_aux(mini, aux, 
				"syntax error near unexpected token", (*current)->content);
		if (aux->in_redir)
		{
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
}
