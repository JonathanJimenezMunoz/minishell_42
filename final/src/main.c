/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyanez-m <dyanez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:40:23 by david             #+#    #+#             */
/*   Updated: 2024/09/02 17:30:54 by dyanez-m         ###   ########.fr       */
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
void print_table(t_table *table)
{
    t_table *current = table;
    int i;

    while (current != NULL)
    {
        printf("Args:\n");
        if (current->args)
        {
            for (i = 0; current->args[i] != NULL; i++)
            {
                printf("\t%s\n", current->args[i]);
            }
        }

        printf("Input Redirection:\n");
        if (current->in_redir)
        {
            for (i = 0; current->in_redir[i] != NULL; i++)
            {
                printf("\t%s\n", current->in_redir[i]);
            }
        }

        printf("Output Redirection:\n");
        if (current->out_redir)
        {
            for (i = 0; current->out_redir[i] != NULL; i++)
            {
                printf("\t%s\n", current->out_redir[i]);
            }
        }

        printf("Heredoc Input:\n");
        if (current->in_heredoc)
        {
            for (i = 0; current->in_heredoc[i] != NULL; i++)
            {
                printf("\t%s\n", current->in_heredoc[i]);
            }
        }

        printf("Append Output:\n");
        if (current->out_append)
        {
            for (i = 0; current->out_append[i] != NULL; i++)
            {
                printf("\t%s\n", current->out_append[i]);
            }
        }

        printf("Last Output Redirection:\n");
        if (current->last_out_redir)
        {
            printf("\t%s\n", current->last_out_redir);
        }

        current = current->next;
        printf("\n");
    }
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
			//process_heredoc(mini);
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
