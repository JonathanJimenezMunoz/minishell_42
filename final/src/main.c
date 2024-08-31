/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:40:23 by david             #+#    #+#             */
/*   Updated: 2024/08/31 16:17:54 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	init_mini(t_mini *mini, char **envp)
{
	mini->line = NULL;
	mini->tokens = NULL;
	mini->table = NULL;
	mini->envp = NULL;
	mini->exit_status = 0;
	mini->exec_envp = NULL;
	envp_init(&mini->envp, envp);
	mini->exec_envp = copy_double_str(envp);
}

static void	ft_loop(t_mini *mini)
{
	while (1)
	{
		//setup_signal_handlers();
		mini->line = readline("msh>>");
		if (!mini->line)
		{
			printf("msh>>exit\n");
			ft_free_all(mini);
			exit(mini->exit_status);
		}
		add_history(mini->line);
		tokenize_line(mini->line, mini);
		token_print(mini->tokens);
	}
}
int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	(void)argc;
	(void)argv;

	init_mini(&mini, envp);
	ft_loop(&mini);
}