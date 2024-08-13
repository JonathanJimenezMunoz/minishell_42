/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handler_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:14:05 by david             #+#    #+#             */
/*   Updated: 2024/08/13 17:37:17 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	parse_cmd_args(t_table_aux *aux, int *first_word, t_token **current)
{
	int	i;

	i = 0;
	if (*first_word == 1 && (*current)->type == TOKEN_WORD)
	{
		aux->cmd = ft_strdup((*current)->content);
		*first_word = 0;
	}
	else if ((*current)->type == TOKEN_WORD)
	{
		while (aux->args && aux->args[i])
			i++;
		aux->args = ft_realloc_args(aux->args, i + 2);
		aux->args[i] = ft_strdup((*current)->content);
		aux->args[i + 1] = NULL;
	}
}

static void	parser_redir_out_aux(t_mini *mini, t_table_aux *aux,
		t_token **current)
{
	if (aux->out_append)
	{
		open_file(aux->out_append, O_WRONLY | O_CREAT | O_APPEND,
			0644, mini);
		free(aux->out_append);
		aux->out_append = NULL;
	}
	if (aux->out_redir)
	{
		open_file(aux->out_redir, O_WRONLY | O_CREAT | O_TRUNC, 0644, mini);
		free(aux->out_redir);
		aux->out_redir = NULL;
	}
	aux->out_redir = ft_strdup((*current)->content);
}

void	parser_redir_out(t_mini *mini, t_table_aux *aux, t_token **current)
{
	if ((*current)->type == TOKEN_REDIR_OUT)
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
		parser_redir_out_aux(mini, aux, current);
	}
}

static void	parse_redir_append_aux(t_mini *mini, t_table_aux *aux,
		t_token **current)
{
	if (aux->out_redir)
	{
		open_file(aux->out_redir, O_WRONLY | O_CREAT | O_TRUNC, 0644, mini);
		free(aux->out_redir);
		aux->out_redir = NULL;
	}
	if (aux->out_append)
	{
		open_file(aux->out_append, O_WRONLY | O_CREAT | O_APPEND,
			0644, mini);
		free(aux->out_append);
		aux->out_append = NULL;
	}
	aux->out_append = ft_strdup((*current)->content);
}

void	parse_redir_append(t_mini *mini, t_table_aux *aux, t_token **current)
{
	if ((*current)->type == TOKEN_REDIR_APPEND)
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
		parse_redir_append_aux(mini, aux, current);
	}
}
