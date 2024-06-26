/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:04:34 by david             #+#    #+#             */
/*   Updated: 2024/06/26 23:46:44 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../headers/minishell.h"

void init_mini(t_mini *mini)
{
    mini->tokens = NULL;
    mini->error = 0;
}

int main(int argc, char **argv, char **envp)
{
	t_mini	mini; // Falta init mini 
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;
	//Faltaria meter el envp en la estructura mini
	while(1) // Falta por saber la flag de parada
	{
		line = readline("msh>> ");
		if (!line)
			break; // frees y toda la movida para acabar
		printf("esta es mi linea: %s\n", line);
		tokenize_line(line, &mini);
		free(line);
		token_print(mini.tokens);
	}
	return (0);
	
}
