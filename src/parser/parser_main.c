/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 22:32:54 by david             #+#    #+#             */
/*   Updated: 2024/06/28 23:37:59 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	init_aux(t_table_aux *aux)
{
	aux->cmd = NULL;
	aux->args = NULL;
	aux->in_redir = NULL;
	aux->out_redir = NULL;
}
int parser_token(t_mini *mini)
{
	t_token     *current;
	t_table     *new_node;
	int         first_word;
	t_table_aux aux;

	first_word = 1;
	current = mini->tokens;
    new_node = mini->table;
	init_cataux(&aux);
    if (current->content == "|")
        ft_error(mini, "syntax error near unexpected token '|'");
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!aux.cmd)
                aux.cmd = NULL;
			if (!aux.in_redir)
                aux.in_redir = NULL;
			if (!aux.out_redir)
                aux.out_redir = NULL;
			if (!aux.args)
                aux.args = NULL;
            add_node(&mini, &aux);
		}
		else if ((first_word == 1) && (current->type == TOKEN_WORD))
		{
			aux.cmd = ft_strdup(current->content);
			first_word = 0;
		}
		else if (current->type == TOKEN_WORD)
		{
			aux.args = ft_strjoin(aux.args, current->content);
		}
		else if (current->type == TOKEN_REDIR_IN)
		{
			if (current->next)
			current = current->next;
			aux.in_redir = current->content;
		}
		else if (current->type == TOKEN_REDIR_OUT)
		{
            if (!current->next)
                ft_error_aux(mini, &aux, 
                    "syntax error near unexpected token `newline'");
			current = current->next;
			aux.out_redir = current->content;
		}
		current = current->next;
	}
	return (0);
}

in_redir, out_redir, cdm, args
first_word = 1
pipe
cat < "Makefile" | grep libft > outfile | wc -l < outfile
while tokens
	if pipe 
		if !in redir 
			in_redir = NULL
		if !out redir
			out_redir = NULL
		if !args
			args = NULL
		create_node (cdm, args, in_redir, out_redir)
		first_word = 1
	if first_word
		cdm = token
		first_word = 0
	else
		args = token + args
	if < or <<
		token->next
		in_redir = token
	else if > or >>
		token->next
		out_redir = token


if !in redir 
	in_redir = NULL
if !out redir
	out_redir = NULL
if !args
	args = NULL
create_node (cdm, args, in_redir, out_redir)