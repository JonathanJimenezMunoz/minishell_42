/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:04:34 by david             #+#    #+#             */
/*   Updated: 2024/07/31 18:50:34 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void init_mini(t_mini *mini)
{
	mini->tokens = NULL;
	mini->table = NULL;
	mini->envp = NULL;
	mini->error = 0;
}

int main(int argc, char **argv, char **envp)
{
	t_mini	mini; // Falta init mini 
	char	*line;

	//Comrprobar numero de args??
	(void)argc;
	(void)argv;
	(void)envp;
	init_mini(&mini);
	envp_init(&mini.envp, envp);

	//envp_print(mini.envp);
	while(1) // Falta por saber la flag de parada
	{
		line = readline("msh>> ");
		if (line)
		{
			add_history(line);
			tokenize_line(line, &mini);
			free(line);
			//token_print(mini.tokens);
			parser_token(&mini);
			// print_table(mini.table);
			execute(&mini, envp);
			free_token_list(&mini.tokens);
			//free_table(&mini.table);
			init_mini(&mini);
			rl_clear_history();
		}
	}
	return (0);
}
