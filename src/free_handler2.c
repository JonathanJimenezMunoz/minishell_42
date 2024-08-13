/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:49:03 by david             #+#    #+#             */
/*   Updated: 2024/08/14 00:23:02 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	ft_free_iteration(t_mini *mini)
{
	free_token_list(&mini->tokens);
	free_table(&mini->table);
	if (mini->error)
	{
		free(mini->error);
		mini->error = NULL;
	}
}
