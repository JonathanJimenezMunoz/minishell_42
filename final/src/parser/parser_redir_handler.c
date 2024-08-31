/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:26:57 by david             #+#    #+#             */
/*   Updated: 2024/08/31 17:23:07 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	parse_redir_in(t_mini *mini, t_table_aux *aux, t_token **current)
{
	int	i;

	i = 0;
	if ((*current)->type == TOKEN_REDIR_IN)
	{
		if (!(*current)->next)
		{
			ft_error(mini, "syntax error near unexpected token", "newline", 2);
			return ;
		}
		*current = (*current)->next;
		if ((*current)->type != TOKEN_WORD)
		{
			ft_error(mini, "syntax error near unexpected token",
				(*current)->content, 2);
			return ;
		}
		while (aux->in_redir && aux->in_redir[i])
			i++;
		aux->in_redir = ft_realloc_double_array(aux->in_redir, i + 1);
		aux->in_redir[i] = ft_strdup((*current)->content);
		aux->in_redir[i + 1] = NULL;
	}
}

void	parse_redir_heredoc(t_mini *mini, t_table_aux *aux, t_token **current)
{
	int	i;

	i = 0;
	if ((*current)->type == TOKEN_REDIR_DELIMITER)
	{
		if (!(*current)->next)
		{
			ft_error(mini, "syntax error near unexpected token", "newline", 2);
			return ;
		}
		*current = (*current)->next;
		if ((*current)->type != TOKEN_WORD)
		{
			ft_error(mini,
				"syntax error near unexpected token", (*current)->content, 2);
			return ;
		}
		while (aux->in_heredoc && aux->in_heredoc[i])
			i++;
		aux->in_heredoc = ft_realloc_double_array(aux->in_heredoc, i + 1);
		aux->in_heredoc[i] = ft_strdup((*current)->content);
		aux->in_heredoc[i + 1] = NULL;
	}
}

void	parse_args(t_table_aux *aux, t_token **current)
{
	int	i;

	i = 0;
	if ((*current)->type == TOKEN_WORD)
	{
		while (aux->args && aux->args[i])
			i++;
		aux->args = ft_realloc_double_array(aux->args, i + 2);
		aux->args[i] = ft_strdup((*current)->content);
		aux->args[i + 1] = NULL;
	}
}

void	parser_redir_out(t_mini *mini, t_table_aux *aux, t_token **current)
{
	int	i;

	i = 0;
	if ((*current)->type == TOKEN_REDIR_OUT)
	{
		if (!(*current)->next)
		{
			ft_error(mini, "syntax error near unexpected token", "newline", 2);
			return ;
		}
		*current = (*current)->next;
		if ((*current)->type != TOKEN_WORD)
		{
			ft_error(mini,
				"syntax error near unexpected token", (*current)->content, );
			return ;
		}
		while (aux->out_redir && aux->out_redir[i])
			i++;
		aux->out_redir = ft_realloc_double_array(aux->out_redir, i + 1);
		aux->out_redir[i] = ft_strdup((*current)->content);
		aux->out_redir[i + 1] = NULL;
	}
}

void	parse_redir_append(t_mini *mini, t_table_aux *aux, t_token **current)
{
	int	i;

	i = 0;
	if ((*current)->type == TOKEN_REDIR_APPEND)
	{
		if (!(*current)->next)
		{
			ft_error(mini, "syntax error near unexpected token", "newline", 2);
			return ;
		}
		*current = (*current)->next;
		if ((*current)->type != TOKEN_WORD)
		{
			ft_error(mini,
				"syntax error near unexpected token", (*current)->content, 2);
			return ;
		}
		while (aux->out_append && aux->out_append[i])
			i++;
		aux->out_append = ft_realloc_double_array(aux->out_append, i + 1);
		aux->out_append[i] = ft_strdup((*current)->content);
		aux->out_append[i + 1] = NULL;	
	}
}
