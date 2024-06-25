/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:04:34 by david             #+#    #+#             */
/*   Updated: 2024/06/25 23:53:47 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../headers/minishell.h"

int main(int argc, char **argv/*, char **envp*/)
{
	t_mini	*mini; // Falta init mini 
	char	*line;

	(void)argc;
	(void)argv;
	//Faltaria meter el envp en la estructura mini
	printf("HOla\n");

	while(1) // Falta por saber la flag de parada
	{
		line = readline("minishell$ ");
		if (!line)
			break; // frees y toda la movida para acabar
		printf("esta es mi linea: %s\n", line);
		tokenize_line(&line, &mini);	
	}
	return (0);
}
