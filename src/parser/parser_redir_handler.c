/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:26:57 by david             #+#    #+#             */
/*   Updated: 2024/09/21 18:13:07 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	parse_redir_in(t_mini *mini, t_table_aux *aux, t_token **current)
{
	if ((*current)->type != TOKEN_REDIR_IN)
		return ;
	if (!(*current)->next)
		return (ft_error_syx(mini, "newline", 2));
	*current = (*current)->next;
	while ((*current) && (*current)->next && (*current)->type == TOKEN_SPACE)
		*current = (*current)->next;
	if ((*current)->type != TOKEN_WORD && (*current)->type != TOKEN_EMPTY
		&& (*current)->type != TOKEN_QUOTES_EMPTY)
		return (ft_error_syx(mini, (*current)->content, 2));
	if ((*current)->type == TOKEN_EMPTY)
		return (ft_error(mini, "ambiguous redirect", "", 1));
	add_redir_end(aux, (*current)->content, TOKEN_REDIR_IN);
}

void	parse_redir_heredoc(t_mini *mini, t_table_aux *aux, t_token **current)
{
	char	*file;

	if ((*current)->type != TOKEN_REDIR_DELIMITER)
		return ;
	if (!(*current)->next)
		return (ft_error_syx(mini, "newline", 2));
	*current = (*current)->next;
	while ((*current) && (*current)->next && (*current)->type == TOKEN_SPACE)
		*current = (*current)->next;
	if ((*current)->type != TOKEN_WORD && (*current)->type != TOKEN_EMPTY
		&& (*current)->type != TOKEN_QUOTES_EMPTY)
		return (ft_error_syx(mini, (*current)->content, 2));
	add_redir_end(aux, (*current)->content, TOKEN_REDIR_DELIMITER);
	file = heredoc_filename();
	add_redir_end(aux, file, TOKEN_UNLINK);
	free(file);
}

void	parse_args(t_table_aux *aux, t_token **current)
{
	int	i;

	i = 0;
	if ((*current)->type == TOKEN_WORD || (*current)->type == TOKEN_EMPTY || \
		(*current)->type == TOKEN_QUOTES_EMPTY)
	{
		if ((*current)->type == TOKEN_EMPTY && !aux->args)
			return ;
		while (aux->args && aux->args[i])
			i++;
		aux->args = ft_realloc_double_array(aux->args, sizeof(char *) * i,
				sizeof(char *) * (i + 2));
		aux->args[i] = ft_strdup((*current)->content);
		aux->args[i + 1] = NULL;
	}
}

void	parser_redir_out(t_mini *mini, t_table_aux *aux, t_token **current)
{
	if ((*current)->type != TOKEN_REDIR_OUT)
		return ;
	if (!(*current)->next)
		return (ft_error_syx(mini, "newline", 2));
	*current = (*current)->next;
	while ((*current) && (*current)->next && (*current)->type == TOKEN_SPACE)
		*current = (*current)->next;
	if ((*current)->type != TOKEN_WORD && (*current)->type != TOKEN_EMPTY
		&& (*current)->type != TOKEN_QUOTES_EMPTY)
		return (ft_error_syx(mini, (*current)->content, 2));
	if ((*current)->type == TOKEN_EMPTY)
		return (ft_error(mini, "ambiguous redirect", "", 1));
	add_redir_end(aux, (*current)->content, TOKEN_REDIR_OUT);
}

void	parse_redir_append(t_mini *mini, t_table_aux *aux, t_token **current)
{
	if ((*current)->type != TOKEN_REDIR_APPEND)
		return ;
	if (!(*current)->next)
		return (ft_error_syx(mini, "newline", 2));
	*current = (*current)->next;
	while ((*current) && (*current)->next && (*current)->type == TOKEN_SPACE)
		*current = (*current)->next;
	if ((*current)->type != TOKEN_WORD && (*current)->type != TOKEN_EMPTY
		&& (*current)->type != TOKEN_QUOTES_EMPTY)
		return (ft_error_syx(mini, (*current)->content, 2));
	if ((*current)->type == TOKEN_EMPTY)
		return (ft_error(mini, "ambiguous redirect", "", 1));
	add_redir_end(aux, (*current)->content, TOKEN_REDIR_APPEND);
}
