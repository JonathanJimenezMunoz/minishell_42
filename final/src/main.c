/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:40:23 by david             #+#    #+#             */
/*   Updated: 2024/09/02 15:29:29 by dyanez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int g_sigint;

static void	init_mini(t_mini *mini, char **envp)
{
	mini->line = NULL;
	mini->tokens = NULL;
	mini->table = NULL;
	mini->envp = NULL;
	mini->exit_status = 0;
	mini->error = 0;
	mini->exec_envp = NULL;
	envp_init(&mini->envp, envp);
	mini->exec_envp = copy_double_str(envp);
}

static void	iteration_handler(t_mini *mini)
{
	free_token_list(&mini->tokens);
	free_table(&mini->table);
	free(mini->line);
	mini->line = NULL;
	mini->tokens = NULL;
	mini->table = NULL;
	mini->error = 0;
}
static void	ft_loop(t_mini *mini)
{
	while (1)
	{
		while_signals(mini);
		mini->line = readline("msh>>");
		if (!mini->line)
		{
			printf("msh>>exit\n");
			ft_free_all(mini);
			exit(mini->exit_status);
		}
		add_history(mini->line);
		tokenize_line(mini->line, mini);
		if (mini->error == 0)
		{	
			parser_token(mini);
			process_heredoc(mini);
			do_redir_handler(mini);
		}
		if (mini->error == 0)
			execute(mini);
		iteration_handler(mini);
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
