/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:26:57 by david             #+#    #+#             */
/*   Updated: 2024/09/01 20:25:04 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	parse_redir_in(t_mini *mini, t_table_aux *aux, t_token **current)
{
	int	i;

	i = 0;
	if ((*current)->type != TOKEN_REDIR_IN)
		return ;
	if (!(*current)->next)
		return (ft_error_syx(mini, "newline", 2));
	*current = (*current)->next;
	while ((*current)->type == TOKEN_SPACE)
		*current = (*current)->next;
	if ((*current)->type != TOKEN_WORD)
		return (ft_error_syx(mini, (*current)->content, 2));
	while (aux->in_redir && aux->in_redir[i])
		i++;
	aux->in_redir = ft_realloc_double_array(aux->in_redir, i + 1);
	aux->in_redir[i] = ft_strdup((*current)->content);
	aux->in_redir[i + 1] = NULL;
}

void	parse_redir_heredoc(t_mini *mini, t_table_aux *aux, t_token **current)
{
	int	i;

	i = 0;
	if ((*current)->type != TOKEN_REDIR_DELIMITER)
		return ;
	if (!(*current)->next)
		return (ft_error_syx(mini, "newline", 2));
	*current = (*current)->next;
	while ((*current)->type == TOKEN_SPACE)
		*current = (*current)->next;
	if ((*current)->type != TOKEN_WORD)
		return (ft_error_syx(mini, (*current)->content, 2));
	while (aux->in_heredoc && aux->in_heredoc[i])
		i++;
	aux->in_heredoc = ft_realloc_double_array(aux->in_heredoc, i + 1);
	aux->in_heredoc[i] = ft_strdup((*current)->content);
	aux->in_heredoc[i + 1] = NULL;
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
	if ((*current)->type != TOKEN_REDIR_OUT)
		return ;
	if (!(*current)->next)
		return (ft_error_syx(mini, "newline", 2));
	*current = (*current)->next;
	while ((*current)->type == TOKEN_SPACE)
		*current = (*current)->next;
	if ((*current)->type != TOKEN_WORD)
		return (ft_error_syx(mini, (*current)->content, 2));
	while (aux->out_redir && aux->out_redir[i])
		i++;
	aux->out_redir = ft_realloc_double_array(aux->out_redir, i + 1);
	aux->out_redir[i] = ft_strdup((*current)->content);
	aux->out_redir[i + 1] = NULL;
	if (aux->last_out_redir)
	{
		free(aux->last_out_redir);
		aux->last_out_redir = NULL;
	}
	aux->last_out_redir = ft_strdup((*current)->content);
	aux->append = 0;
}

void	parse_redir_append(t_mini *mini, t_table_aux *aux, t_token **current)
{
	int	i;

	i = 0;
	if ((*current)->type != TOKEN_REDIR_APPEND)
		return ;
	if (!(*current)->next)
		return (ft_error_syx(mini, "newline", 2));
	*current = (*current)->next;
	while ((*current)->type == TOKEN_SPACE)
		*current = (*current)->next;
	if ((*current)->type != TOKEN_WORD)
		return (ft_error_syx(mini,(*current)->content, 2));
	while (aux->out_append && aux->out_append[i])
		i++;
	aux->out_append = ft_realloc_double_array(aux->out_append, i + 1);
	aux->out_append[i] = ft_strdup((*current)->content);
	aux->out_append[i + 1] = NULL;
	if (aux->last_out_redir)
	{
		free(aux->last_out_redir);
		aux->last_out_redir = NULL;
	}
	aux->last_out_redir = ft_strdup((*current)->content);
	aux->append = 1;
}
