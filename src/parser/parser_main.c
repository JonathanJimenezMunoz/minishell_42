/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 22:32:54 by david             #+#    #+#             */
/*   Updated: 2024/08/21 17:16:55 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*void	print_table(t_table *table)
{
	t_table *current;
	int i, j;

	i = 0;
	current = table;
	while (current)
	{
		printf("Node %d\n", i);
		if (current->cmd)
			printf("cmd: %s\n", current->cmd);
		if (current->args)
		{
			printf("args:\n");
			j = 0;
			while (current->args[j])
			{
				printf("  arg[%d]: %s\n", j, current->args[j]);
				j++;
			}
		}
		if (current->in_redir)
			printf("in_redir: %s\n", current->in_redir);
		if (current->out_redir)
			printf("out_redir: %s\n", current->out_redir);
		if (current->in_heredoc)
			printf("in_heredoc: %s\n", current->in_heredoc);
		if (current->out_append)
			printf("out_append: %s\n", current->out_append);
		i++;
		current = current->next;
	}
}*/

char	**ft_realloc_args(char **args, int new_size)
{
	char	**new_args;
	int		i;

	i = 0;
	new_args = (char **)malloc(new_size * sizeof(char *));
	if (!new_args)
		return (NULL);
	while (args && args[i])
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i] = NULL;
	free(args);
	return (new_args);
}

void	init_aux(t_table_aux *aux)
{
	aux->cmd = NULL;
	aux->args = NULL;
	aux->in_redir = NULL;
	aux->out_redir = NULL;
	aux->out_append = NULL;
	aux->in_heredoc = NULL;
}

static void	parse_while(t_mini *mini, t_table_aux *aux,
	int *first_word, t_token **current)
{
	if ((*current)->type == TOKEN_PIPE)
	{
		if (!(*current)->next)
			ft_error(mini, "syntax error near unexpected token",
				(*current)->content);
		if ((*current)->next && (*current)->next->type == TOKEN_PIPE)
			ft_error_aux(mini, aux, "syntax error near unexpected token",
				(*current)->next->content);
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

int	parser_token(t_mini *mini)
{
	t_token		*current;
	int			first_word;
	t_table_aux	aux;

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
