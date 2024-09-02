/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:40:23 by david             #+#    #+#             */
/*   Updated: 2024/09/02 23:36:36 by david            ###   ########.fr       */
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
	mini->pipes = 0;
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
	mini->pipes = 0;
}

void print_redirections(t_redir *redir)
{
    while (redir != NULL)
    {
        printf("\tRedirection: File = %s, Type = %d\n", redir->file, redir->type);
        redir = redir->next;
    }
}

void print_table(t_table *table)
{
    int i;

    while (table != NULL)
    {
        // Imprimir args
        printf("Args:\n");
        if (table->args != NULL)
        {
            for (i = 0; table->args[i] != NULL; i++)
            {
                printf("\t%s\n", table->args[i]);
            }
        }

        // Imprimir redirecciones
        if (table->redir != NULL)
        {
            print_redirections(table->redir);
        }

        // Imprimir in_heredoc
        printf("In Heredoc:\n");
        if (table->in_heredoc != NULL)
        {
            for (i = 0; table->in_heredoc[i] != NULL; i++)
            {
                printf("\t%s\n", table->in_heredoc[i]);
            }
        }

        table = table->next;
        printf("\n"); // Separar las entradas de la tabla
    }
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
			mini->pipes = ft_count_pipes(mini);
			//do_redir_handler(mini);
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
